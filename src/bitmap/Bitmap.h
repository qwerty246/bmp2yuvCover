#pragma once

class Bitmap
{
public:
	Bitmap() = default;
	virtual ~Bitmap() = default;

	virtual void FillBitmap(const char* pFileMap) = 0;
protected:
	long CharToLong(unsigned char* pStr) const;
};
