#include "Bitmap.h"
#include <cmath>

unsigned long Bitmap::CharToLong(uchar* pStr) const
{
	unsigned long res = 0;
	for (short i = 0; i < 4; i++)
	{
		unsigned long temp = static_cast<unsigned long>(*(pStr + i));
		res += temp * static_cast<unsigned long>(std::pow(0x100, i));
	}
	return res;
}
