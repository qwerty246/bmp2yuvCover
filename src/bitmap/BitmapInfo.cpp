#include <bitmap/BitmapInfo.h>

BitmapInfo::BitmapInfo() :
	_size(4, 0x0E),
	_width(4, 0x12),
	_height(4, 0x16),
	_planes(2, 0x1A),
	_bitCount(2, 0x1C),
	_compression(4, 0x1E),
	_sizeImage(4, 0x22),
	_xPelsPerMeter(4, 0x26),
	_yPelsPerMeter(4, 0x2A),
	_clrUsed(4, 0x2E),
	_clrImportant(4, 0x32)
{
}

ulong BitmapInfo::GetWidth() const
{
	return _width.GetValue();
}

ulong BitmapInfo::GetHeight() const
{
	return _height.GetValue();
}

void BitmapInfo::FillBitmap(const char* pFileMap)
{
	_size.SetValue(pFileMap + _size.GetPos());
	_width.SetValue(CharToLong((uchar*)(pFileMap + _width.GetPos())));
	_height.SetValue(CharToLong((uchar*)(pFileMap + _height.GetPos())));
	_planes.SetValue(pFileMap + _planes.GetPos());
	_bitCount.SetValue(pFileMap + _bitCount.GetPos());
	_compression.SetValue(pFileMap + _compression.GetPos());
	_sizeImage.SetValue(CharToLong((uchar*)(pFileMap + _sizeImage.GetPos())));
	_xPelsPerMeter.SetValue(pFileMap + _xPelsPerMeter.GetPos());
	_yPelsPerMeter.SetValue(pFileMap + _yPelsPerMeter.GetPos());
	_clrUsed.SetValue(pFileMap + _clrUsed.GetPos());
	_clrImportant.SetValue(pFileMap + _clrImportant.GetPos());
}
