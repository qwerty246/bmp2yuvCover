#include <bitmap/ParamChar.h>

ParamChar::ParamChar(ushort uSize, ushort uPos) :
	Param(uSize, uPos),
	_pValue(nullptr)
{
}

void ParamChar::SetValue(const char* pValue)
{
	_pValue = pValue;
}
