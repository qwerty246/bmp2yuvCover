#pragma once

#include "Param.h"

class ParamChar : public Param
{
public:
	ParamChar(unsigned long uSize, unsigned long uPos);
	~ParamChar() = default;

	void SetValue(const char* pValue);
private:
	const char* _pValue;
};
