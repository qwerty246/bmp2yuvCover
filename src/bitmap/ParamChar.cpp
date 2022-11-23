#include "ParamChar.h"

ParamChar::ParamChar(unsigned long uSize, unsigned long uPos) :
	Param(uSize, uPos),
	_pValue(nullptr)
{
}

void ParamChar::SetValue(const char* pValue)
{
	_pValue = pValue;
}
