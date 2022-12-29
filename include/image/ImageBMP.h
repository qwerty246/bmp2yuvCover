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

	bool OpenAndReadFile(const std::string& sFileName);
	ulong GetWidth() const;
	ulong GetHeight() const;
	const char* GetDataMap() const;
private:
	char* m_pFileMap;
	bool m_bIsOpened;
	std::ifstream m_ifstream;
	BitmapFileHeader m_bitmapFileHeader;
	BitmapInfo m_bitmapInfo;

	enum
	{
		BITMAP_SIZE = 54
	};
};
