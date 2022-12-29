#include <image/ImageBMP.h>
#include <iostream>

ImageBMP::ImageBMP() :
	m_pFileMap(nullptr),
	m_bIsOpened(false)
{
}

ImageBMP::~ImageBMP()
{
	if (m_pFileMap)
	{
		delete[] m_pFileMap;
	}
}

bool ImageBMP::OpenAndReadFile(const std::string& sFileName)
{
	m_ifstream.open(sFileName, std::ios::binary);
	if (!m_ifstream)
	{
		m_bIsOpened = false;
		return false;
	}
	m_bIsOpened = true;

	try
	{
		ulong lFileSize = m_bitmapFileHeader.ReadAndGetFileSize(m_ifstream);
		if (m_pFileMap)
		{
			delete[] m_pFileMap;
		}
		m_pFileMap = new char[lFileSize];
		m_ifstream.seekg(std::ios::beg);
		m_ifstream.read(m_pFileMap, lFileSize);
		m_ifstream.close();
	}
	catch (...)
	{
		std::cout << "An error occurred while reading file \"" + sFileName + "\"." << std::endl;
		return false;
	}

	m_bitmapFileHeader.FillBitmap(m_pFileMap);
	m_bitmapInfo.FillBitmap(m_pFileMap);
	return true;
}

ulong ImageBMP::GetWidth() const
{
	if (!m_bIsOpened)
	{
		return 0;
	}
	return m_bitmapInfo.GetWidth();
}

ulong ImageBMP::GetHeight() const
{
	if (!m_bIsOpened)
	{
		return 0;
	}
	return m_bitmapInfo.GetHeight();
}

const char* ImageBMP::GetDataMap() const
{
	if (!m_bIsOpened)
	{
		return nullptr;
	}
	return m_pFileMap + BITMAP_SIZE;
}
