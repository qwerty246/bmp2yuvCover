#pragma once

typedef unsigned short ushort;

class Param
{
public:
	Param(ushort nSize, ushort nPos) : m_nSize(nSize), m_nPos(nPos) {};
	virtual ~Param() = default;

	ushort GetSize() const;
	ushort GetPos() const;
private:
	const ushort m_nSize;
	const ushort m_nPos;
};
