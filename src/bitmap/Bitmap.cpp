#include "Bitmap.h"
#include <cmath>

long Bitmap::CharToLong(unsigned char* pStr) const
{
	unsigned long res = 0;
	for (size_t i = 0; i < 4; i++)
	{
		unsigned long temp = static_cast<unsigned long>(*(pStr + i));
		res += temp * static_cast<unsigned long>(std::pow(0x100, i));
	}
	return res;
}
