#pragma once

#include "Param.h"

class ParamChar : public Param
{
public:
	ParamChar(ushort uSize, ushort uPos);
	~ParamChar() = default;

	void SetValue(const char* pValue);
private:
	const char* _pValue;
};
