#pragma once

#include "Bitmap.h"
#include "ParamChar.h"
#include "ParamLong.h"

#include <fstream>

class BitmapFileHeader : public Bitmap
{
public:
	BitmapFileHeader();
	~BitmapFileHeader() = default;

	unsigned long ReadAndGetFileSize(std::ifstream& ifstream);
	void FillBitmap(const char* pFileMap) override;
private:
	ParamChar _type;		// 0x4D 0x42 mark
	ParamLong _size;		// File size
	ParamChar _reserved1;	// Reserved
	ParamChar _reserved2;	// Reserved
	ParamChar _offBits;		// Pixel data position
};
