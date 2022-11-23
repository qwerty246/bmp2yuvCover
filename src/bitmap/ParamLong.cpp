#include "ParamLong.h"

ParamLong::ParamLong(unsigned long uSize, unsigned long uPos) :
	Param(uSize, uPos),
	_pValue(0)
{
}

void ParamLong::SetValue(unsigned long pValue)
{
	_pValue = pValue;
}

unsigned long ParamLong::GetValue() const
{
	return _pValue;
}
