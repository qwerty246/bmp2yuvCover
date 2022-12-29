#pragma once

#include "Param.h"

typedef unsigned long ulong;

class ParamLong : public Param
{
public:
	ParamLong(ushort nSize, ushort nPos);
	~ParamLong() = default;

	void SetValue(ulong lValue);
	ulong GetValue() const;
private:
	ulong m_lValue;
};
