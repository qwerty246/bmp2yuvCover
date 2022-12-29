#include <image/ImageYUV.h>

#include <iostream>
#include <vector>
#include <thread>

ImageYUV::ImageYUV() :
	m_lWidth(0),
	m_lHeight(0),
	m_lFrames(0),
	m_bIsOpened(false)
{
}

ImageYUV::~ImageYUV()
{
}

bool ImageYUV::OpenFile(std::string sFileName, ulong lWidth, ulong lHeight, ulong lFrames)
{
	m_ofstream.open(sFileName, std::fstream::binary | std::fstream::in | std::fstream::out);
	if (!m_ofstream)
	{
		m_bIsOpened = false;
		return false;
	}
	m_sFileName = sFileName;
	m_lWidth = lWidth;
	m_lHeight = lHeight;
	m_lFrames = lFrames;
	m_bIsOpened = true;
	return true;
}

bool ImageYUV::OverlayImage(const ImageBMP& file)
{
	if (!m_bIsOpened)
	{
		std::cout << "Error: unable to open file \"" + m_sFileName + "\"." << std::endl;
		return false;
	}
	if (file.GetWidth() > m_lWidth)
	{
		std::cout << "Error: width of BMP file is larger than width of YUV file." << std::endl;
		return false;
	}
	if (file.GetHeight() > m_lHeight)
	{
		std::cout << "Error: height of BMP file is larger than height of YUV file." << std::endl;
		return false;
	}
	std::vector <std::thread> vThreads;
	ulong i = 0;
	try
	{
		while (i < m_lFrames)
		{
			for (short j = 0; j < std::thread::hardware_concurrency() && i < m_lFrames; i++, j++)
			{
				vThreads.push_back(std::thread(&ImageYUV::OverlayImageOnFrame, this, std::ref(file), i));
			}
			for (std::thread& th : vThreads)
			{
				if (th.joinable())
				{
					th.join();
				}
			}
			vThreads.clear();
		}
	}
	catch (...)
	{
		std::cout << "An error occurred while writing file \"" + m_sFileName + "\"." << std::endl;
		return false;
	}
	return true;
}

void ImageYUV::OverlayImageOnFrame(const ImageBMP& file, ulong lFrame)
{
	if (lFrame > m_lFrames)
	{
		return;
	}
	const char* pFileMap = file.GetDataMap();
	size_t uPosPage = static_cast<size_t>(lFrame * m_lWidth * m_lHeight * 1.5);
	size_t uPosU = m_lWidth * m_lHeight;
	size_t uPosV = static_cast<size_t>(m_lWidth * m_lHeight * 1.25);
	for (ulong i = 0; i < file.GetHeight(); i++)
	{
		for (ulong j = 0; j < file.GetWidth(); j++)
		{
			uchar uB = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j];
			uchar uG = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j + 1];
			uchar uR = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j + 2];

			m_mutex.lock();
			m_ofstream.seekp(uPosPage + i * m_lWidth + j);
			m_ofstream << GetSum(0.299 * uR, 0.587 * uG, 0.114 * uB, 0);
			m_mutex.unlock();

			if ((i % 2 == 0) &&
				(j % 2 == 0))
			{
				m_mutex.lock();
				m_ofstream.seekp(uPosPage + uPosU + i * m_lWidth / 4 + j / 2);
				m_ofstream << GetSum(-0.169 * uR, -0.331 * uG, 0.500 * uB, 128);
				m_ofstream.seekp(uPosPage + uPosV + i * m_lWidth / 4 + j / 2);
				m_ofstream << GetSum(0.500 * uR, -0.419 * uG, -0.081 * uB, 128);
				m_mutex.unlock();
			}
		}
	}
}

uchar ImageYUV::GetSum(double dR, double dG, double dB, short nX) const
{
	double dSum = dR + dG + dB + nX;
	if (dSum > 255)
	{
		return 255;
	}
	if (dSum < 0)
	{
		return 0;
	}
	return static_cast<uchar>(dSum);
}
