#pragma once

#include "Param.h"

typedef unsigned long ulong;

class ParamLong : public Param
{
public:
	ParamLong(ushort uSize, ushort uPos);
	~ParamLong() = default;

	void SetValue(ulong pValue);
	ulong GetValue() const;
private:
	ulong _pValue;
};
