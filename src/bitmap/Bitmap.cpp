#include <bitmap/Bitmap.h>
#include <cmath>

unsigned long Bitmap::CharToLong(const uchar* pStr) const
{
	unsigned long lRes = 0;
	for (short i = 0; i < 4; i++)
	{
		unsigned long lTemp = static_cast<unsigned long>(*(pStr + i));
		lRes += lTemp * static_cast<unsigned long>(std::pow(0x100, i));
	}
	return lRes;
}
