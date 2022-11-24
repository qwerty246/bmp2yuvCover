#include "ImageYUV.h"

#include <iostream>
#include <vector>
#include <thread>

ImageYUV::ImageYUV() :
	_uWidth(0),
	_uHeight(0),
	_uFrames(0),
	_bIsOpened(false)
{
}

ImageYUV::~ImageYUV()
{
}

bool ImageYUV::OpenFile(std::string sFileName, ulong uWidth, ulong uHeight, ulong uFrames)
{
	_ofstream.open(sFileName, std::fstream::binary | std::fstream::in | std::fstream::out);
	if (!_ofstream)
	{
		_bIsOpened = false;
		return false;
	}
	_uWidth = uWidth;
	_uHeight = uHeight;
	_uFrames = uFrames;
	_bIsOpened = true;
	return true;
}

bool ImageYUV::OverlayImage(const ImageBMP& file)
{
	if (!_bIsOpened)
	{
		return false;
	}
	if (file.GetWidth() > _uWidth)
	{
		return false;
	}
	if (file.GetHeight() > _uHeight)
	{
		return false;
	}
	std::vector <std::thread> vThreads;
	short maxThreads = std::thread::hardware_concurrency();
	ulong i = 0;
	try
	{
		while (i < _uFrames)
		{
			for (short j = 0; j < maxThreads && i < _uFrames; i++, j++)
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
		return false;
	}
	return true;
}

void ImageYUV::OverlayImageOnFrame(const ImageBMP& file, ulong uFrame)
{
	if (uFrame > _uFrames)
	{
		return;
	}
	const char* pFileMap = file.GetDataMap();
	size_t uPosPage = static_cast<size_t>(uFrame * _uWidth * _uHeight * 1.5);
	size_t uPosU = _uWidth * _uHeight;
	size_t uPosV = static_cast<size_t>(_uWidth * _uHeight * 1.25);
	for (ulong i = 0; i < file.GetHeight(); i++)
	{
		for (ulong j = 0; j < file.GetWidth(); j++)
		{
			uchar B = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j];
			uchar G = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j + 1];
			uchar R = pFileMap[3 * file.GetWidth() * (file.GetHeight() - i - 1) + 3 * j + 2];

			uchar Y = GetSum(0.299 * R, 0.587 * G, 0.114 * B, 0);

			_mutex.lock();
			_ofstream.seekp(uPosPage + i * _uWidth + j);
			_ofstream << Y;
			_mutex.unlock();
			if ((i % 2 == 0) &&
				(j % 2 == 0))
			{
				uchar U = GetSum(-0.169 * R, -0.331 * G, 0.500 * B, 128);
				uchar V = GetSum(0.500 * R, -0.419 * G, -0.081 * B, 128);
				_mutex.lock();
				_ofstream.seekp(uPosPage + uPosU + i * _uWidth / 4 + j / 2);
				_ofstream << U;
				_ofstream.seekp(uPosPage + uPosV + i * _uWidth / 4 + j / 2);
				_ofstream << V;
				_mutex.unlock();
			}
		}
	}
}

uchar ImageYUV::GetSum(double R, double G, double B, short x) const
{
	double sum = R + G + B + x;
	if (sum > 255)
	{
		return 255;
	}
	if (sum < 0)
	{
		return 0;
	}
	return static_cast<uchar>(sum);
}
