#include "ParamLong.h"

ParamLong::ParamLong(ushort uSize, ushort uPos) :
	Param(uSize, uPos),
	_pValue(0)
{
}

void ParamLong::SetValue(ulong pValue)
{
	_pValue = pValue;
}

ulong ParamLong::GetValue() const
{
	return _pValue;
}
