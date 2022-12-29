#pragma once

#include "Param.h"

class ParamChar : public Param
{
public:
	ParamChar(ushort nSize, ushort nPos);
	~ParamChar() = default;

	void SetValue(const char* pValue);
private:
	const char* m_pValue;
};
