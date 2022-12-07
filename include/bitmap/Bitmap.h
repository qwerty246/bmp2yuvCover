#pragma once

typedef unsigned char uchar;

class Bitmap
{
public:
	Bitmap() = default;
	virtual ~Bitmap() = default;

	virtual void FillBitmap(const char* pFileMap) = 0;
protected:
	unsigned long CharToLong(uchar* pStr) const;
};
