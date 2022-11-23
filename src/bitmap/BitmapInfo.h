#pragma once

#include "Bitmap.h"
#include "ParamChar.h"
#include "ParamLong.h"

struct BitmapInfo : public Bitmap
{
	BitmapInfo();
	~BitmapInfo() = default;

	unsigned long GetWidth() const;
	unsigned long GetHeight() const;

	void FillBitmap(const char* pFileMap) override;
private:
	ParamChar _size;			// This struct size (40, because of 3 version)
	ParamLong _width;			// Width
	ParamLong _height;			// Height
	ParamChar _planes;			// Reserved
	ParamChar _bitCount;		// Number of bits per pixel
	ParamChar _compression;		// Way to store pixels
	ParamLong _sizeImage;		// Pixel data size
	ParamChar _xPelsPerMeter;	// Number of pixels per meter horizontally
	ParamChar _yPelsPerMeter;	// Number of pixels per meter vertically
	ParamChar _clrUsed;			// Color table size
	ParamChar _clrImportant;	// Number of cells from the beginning of the color table to the last used
};
