#pragma once

#include "bitmap/Param.h"

class ParamLong : public Param
{
public:
	ParamLong(unsigned long uSize, unsigned long uPos);
	~ParamLong() = default;

	void SetValue(unsigned long pValue);
	unsigned long GetValue() const;
private:
	unsigned long _pValue;
};
