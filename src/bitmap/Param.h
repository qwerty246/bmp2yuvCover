#pragma once

class Param
{
public:
	Param(unsigned long uSize, unsigned long uPos) : _uSize(uSize), _uPos(uPos) {};
	virtual ~Param() = default;

	unsigned long GetSize() const;
	unsigned long GetPos() const;
private:
	const unsigned long _uSize;
	const unsigned long _uPos;
};
