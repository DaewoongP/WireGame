#pragma once
#include "Include.h"

class CLine
{
public:
	CLine();
	CLine(MYPOINT& tLeft, MYPOINT& tRight);
	CLine(LINE& tLine);
	~CLine();

public:
	const LINE&		Get_Info()const { return m_tInfo; }

public:
	void		Render(HDC _hDC);
private:
	LINE		m_tInfo;
	PENINFO		m_tPenInfo;
};

