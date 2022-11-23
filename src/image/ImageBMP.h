#pragma once

#include <bitmap/BitmapFileHeader.h>
#include <bitmap/BitmapInfo.h>

#include <fstream>
#include <string>

class ImageBMP
{
public:
	ImageBMP();
	~ImageBMP();

	bool OpenAndReadFile(std::string sFileName);
	unsigned long GetWidth() const;
	unsigned long GetHeight() const;
	const char* GetDataMap() const;
private:
	char* _pFileMap;
	bool _bIsOpened;

	std::ifstream _ifstream;
	BitmapFileHeader _bitmapFileHeader;
	BitmapInfo _bitmapInfo;

	enum
	{
		BITMAP_SIZE = 54
	};
};
