#include "ImageBMP.h"
#include <iostream>

ImageBMP::ImageBMP() :
	_pFileMap(nullptr),
	_bIsOpened(false)
{
}

ImageBMP::~ImageBMP()
{
	if (_pFileMap)
	{
		delete[] _pFileMap;
	}
}

bool ImageBMP::OpenAndReadFile(std::string sFileName)
{
	_ifstream.open(sFileName, std::ios::binary);
	if (!_ifstream)
	{
		std::cout << "Error: unable to open file \"" + sFileName + "\"." << std::endl;
		_bIsOpened = false;
		return false;
	}
	_bIsOpened = true;

	try
	{
		ulong uFileSize = _bitmapFileHeader.ReadAndGetFileSize(_ifstream);
		if (_pFileMap)
		{
			delete[] _pFileMap;
		}
		_pFileMap = new char[uFileSize];
		_ifstream.seekg(std::ios::beg);
		_ifstream.read(_pFileMap, uFileSize);
		_ifstream.close();
	}
	catch (...)
	{
		std::cout << "An error occurred while reading file \"" + sFileName + "\"." << std::endl;
		return false;
	}

	_bitmapFileHeader.FillBitmap(_pFileMap);
	_bitmapInfo.FillBitmap(_pFileMap);

	return true;
}

ulong ImageBMP::GetWidth() const
{
	if (!_bIsOpened)
	{
		return 0;
	}
	return _bitmapInfo.GetWidth();
}

ulong ImageBMP::GetHeight() const
{
	if (!_bIsOpened)
	{
		return 0;
	}
	return _bitmapInfo.GetHeight();
}

const char* ImageBMP::GetDataMap() const
{
	if (!_bIsOpened)
	{
		return nullptr;
	}
	return _pFileMap + BITMAP_SIZE;
}
