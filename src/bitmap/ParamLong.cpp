#include <bitmap/ParamLong.h>

ParamLong::ParamLong(ushort nSize, ushort nPos) :
	Param(nSize, nPos),
	m_lValue(0)
{
}

void ParamLong::SetValue(ulong lValue)
{
	m_lValue = lValue;
}

ulong ParamLong::GetValue() const
{
	return m_lValue;
}
