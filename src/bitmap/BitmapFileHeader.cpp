#include "BitmapFileHeader.h"

BitmapFileHeader::BitmapFileHeader() :
	_type(2, 0x00),
	_size(4, 0x02),
	_reserved1(2, 0x06),
	_reserved2(2, 0x08),
	_offBits(4, 0x0A)
{
}

unsigned long BitmapFileHeader::ReadAndGetFileSize(std::ifstream& ifstream)
{
	unsigned char pBuf[4];
	ifstream.seekg(_type.GetSize());
	for (size_t i = 0; i < 4; i++)
	{
		ifstream >> pBuf[i];
	}
	_size.SetValue(CharToLong(pBuf));
	return _size.GetValue();
}

void BitmapFileHeader::FillBitmap(const char* pFileMap)
{
	_type.SetValue(pFileMap);
	_reserved1.SetValue(pFileMap + _reserved1.GetPos());
	_reserved2.SetValue(pFileMap + _reserved2.GetPos());
	_offBits.SetValue(pFileMap + _offBits.GetPos());
}
