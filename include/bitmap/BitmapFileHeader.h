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

	ulong ReadAndGetFileSize(std::ifstream& ifstream);
	void FillBitmap(const char* pFileMap) override;
private:
	ParamChar m_type;		// 0x4D 0x42 mark
	ParamLong m_size;		// File size
	ParamChar m_reserved1;	// Reserved
	ParamChar m_reserved2;	// Reserved
	ParamChar m_offBits;	// Pixel data position
};
