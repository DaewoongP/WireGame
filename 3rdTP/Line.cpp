#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}


CLine::CLine(MYPOINT& tLeft, MYPOINT& tRight)
	: m_tInfo(tLeft, tRight)
{
}

CLine::CLine(LINE& tLine)
{
	memcpy(&m_tInfo, &tLine, sizeof(LINE));
}

CLine::~CLine()
{
}

void CLine::Render(HDC _hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	m_tPenInfo.CurPen = CreatePen(PS_SOLID, 3, RGB(100, 255, 255));
	m_tPenInfo.CurBrush = CreateSolidBrush(RGB(100, 255, 255));
	m_tPenInfo.OldPen = (HPEN)SelectObject(_hDC, m_tPenInfo.CurPen);
	m_tPenInfo.OldBrush = (HBRUSH)SelectObject(_hDC, m_tPenInfo.CurBrush);

	MoveToEx(_hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(_hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY);

	DeleteObject(m_tPenInfo.OldPen);
	DeleteObject(m_tPenInfo.OldBrush);
}

