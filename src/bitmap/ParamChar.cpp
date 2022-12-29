#include <bitmap/ParamChar.h>

ParamChar::ParamChar(ushort nSize, ushort nPos) :
	Param(nSize, nPos),
	m_pValue(nullptr)
{
}

void ParamChar::SetValue(const char* pValue)
{
	m_pValue = pValue;
}
