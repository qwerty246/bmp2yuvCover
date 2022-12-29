#pragma once

#include "Bitmap.h"
#include "ParamChar.h"
#include "ParamLong.h"

struct BitmapInfo : public Bitmap
{
	BitmapInfo();
	~BitmapInfo() = default;

	ulong GetWidth() const;
	ulong GetHeight() const;
	void FillBitmap(const char* pFileMap) override;
private:
	ParamChar m_size;			// This struct size (40, because of 3 version)
	ParamLong m_width;			// Width
	ParamLong m_height;			// Height
	ParamChar m_planes;			// Reserved
	ParamChar m_bitCount;		// Number of bits per pixel
	ParamChar m_compression;	// Way to store pixels
	ParamLong m_sizeImage;		// Pixel data size
	ParamChar m_xPelsPerMeter;	// Number of pixels per meter horizontally
	ParamChar m_yPelsPerMeter;	// Number of pixels per meter vertically
	ParamChar m_clrUsed;		// Color table size
	ParamChar m_clrImportant;	// Number of cells from the beginning of the color table to the last used
};
