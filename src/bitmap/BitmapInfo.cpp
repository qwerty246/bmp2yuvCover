#include <bitmap/BitmapInfo.h>

BitmapInfo::BitmapInfo() :
	m_size(4, 0x0E),
	m_width(4, 0x12),
	m_height(4, 0x16),
	m_planes(2, 0x1A),
	m_bitCount(2, 0x1C),
	m_compression(4, 0x1E),
	m_sizeImage(4, 0x22),
	m_xPelsPerMeter(4, 0x26),
	m_yPelsPerMeter(4, 0x2A),
	m_clrUsed(4, 0x2E),
	m_clrImportant(4, 0x32)
{
}

ulong BitmapInfo::GetWidth() const
{
	return m_width.GetValue();
}

ulong BitmapInfo::GetHeight() const
{
	return m_height.GetValue();
}

void BitmapInfo::FillBitmap(const char* pFileMap)
{
	m_size.SetValue(pFileMap + m_size.GetPos());
	m_width.SetValue(CharToLong((uchar*)(pFileMap + m_width.GetPos())));
	m_height.SetValue(CharToLong((uchar*)(pFileMap + m_height.GetPos())));
	m_planes.SetValue(pFileMap + m_planes.GetPos());
	m_bitCount.SetValue(pFileMap + m_bitCount.GetPos());
	m_compression.SetValue(pFileMap + m_compression.GetPos());
	m_sizeImage.SetValue(CharToLong((uchar*)(pFileMap + m_sizeImage.GetPos())));
	m_xPelsPerMeter.SetValue(pFileMap + m_xPelsPerMeter.GetPos());
	m_yPelsPerMeter.SetValue(pFileMap + m_yPelsPerMeter.GetPos());
	m_clrUsed.SetValue(pFileMap + m_clrUsed.GetPos());
	m_clrImportant.SetValue(pFileMap + m_clrImportant.GetPos());
}
