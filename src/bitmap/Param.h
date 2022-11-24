#pragma once

typedef unsigned short ushort;

class Param
{
public:
	Param(ushort uSize, ushort uPos) : _uSize(uSize), _uPos(uPos) {};
	virtual ~Param() = default;

	ushort GetSize() const;
	ushort GetPos() const;
private:
	const ushort _uSize;
	const ushort _uPos;
};
