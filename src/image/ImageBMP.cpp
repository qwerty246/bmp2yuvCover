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
		_bIsOpened = false;
		return false;
	}
	_bIsOpened = true;

	try
	{
		unsigned long uFileSize = _bitmapFileHeader.ReadAndGetFileSize(_ifstream);
		_pFileMap = new char[uFileSize];
		_ifstream.seekg(std::ios::beg);
		_ifstream.read(_pFileMap, uFileSize);
		_ifstream.close();
	}
	catch (...)
	{
		return false;
	}

	_bitmapFileHeader.FillBitmap(_pFileMap);
	_bitmapInfo.FillBitmap(_pFileMap);

	return true;
}

unsigned long ImageBMP::GetWidth() const
{
	if (!_bIsOpened)
	{
		return 0;
	}
	return _bitmapInfo.GetWidth();
}

unsigned long ImageBMP::GetHeight() const
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
