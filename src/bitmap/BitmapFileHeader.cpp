#include <bitmap/BitmapFileHeader.h>

BitmapFileHeader::BitmapFileHeader() :
	m_type(2, 0x00),
	m_size(4, 0x02),
	m_reserved1(2, 0x06),
	m_reserved2(2, 0x08),
	m_offBits(4, 0x0A)
{
}

ulong BitmapFileHeader::ReadAndGetFileSize(std::ifstream& ifstream)
{
	uchar pBuf[4];
	ifstream.seekg(m_type.GetSize());
	for (short i = 0; i < 4; i++)
	{
		ifstream >> pBuf[i];
	}
	m_size.SetValue(CharToLong(pBuf));
	return m_size.GetValue();
}

void BitmapFileHeader::FillBitmap(const char* pFileMap)
{
	m_type.SetValue(pFileMap);
	m_reserved1.SetValue(pFileMap + m_reserved1.GetPos());
	m_reserved2.SetValue(pFileMap + m_reserved2.GetPos());
	m_offBits.SetValue(pFileMap + m_offBits.GetPos());
}
