#include "stdafx.h"
#include "Brick.h"
#include "ScrollMgr.h"

CBrick::CBrick()
	:m_fBrickSize(50.f)
{
}


CBrick::~CBrick()
{
	Release();
}

void CBrick::Initialize(void)
{
	m_tInfo.vLook = { 1.f , 0.f , 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 1.f };
	m_PointIndex = 4;
	m_vPoint[0] = {-m_fBrickSize, -m_fBrickSize, 0.f };
	m_vPoint[1] = { m_fBrickSize, -m_fBrickSize, 0.f };
	m_vPoint[2] = { m_fBrickSize,  m_fBrickSize, 0.f };
	m_vPoint[3] = {-m_fBrickSize,  m_fBrickSize, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];
	m_bRandSize = true;
}

int CBrick::Update(void)
{
	if (m_bRandSize)
	{
		m_tInfo.vSize.x = (rand() % 4) / 2 + 1;
		m_tInfo.vSize.y = (rand() * rand() % 4) / 2 + 1;
	}
	
	for (int i = 0; i < 4; ++i)
		m_vPoint[i] = World_Trans(m_vOriginPoint[i], true);

	return OBJ_NOEVENT;
}

void CBrick::Late_Update(void)
{
}

void CBrick::Render(HDC hDC)
{
	int		iScrollX = (int)SCROLL->Get_ScrollX();
	m_tPenInfo.CurPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	m_tPenInfo.CurBrush = CreateSolidBrush(RGB(0, 0, 255));
	m_tPenInfo.OldPen = (HPEN)SelectObject(hDC, m_tPenInfo.CurPen);
	m_tPenInfo.OldBrush = (HBRUSH)SelectObject(hDC, m_tPenInfo.CurBrush);
	MoveToEx(hDC, (int)m_vPoint[0].x + iScrollX,
		(int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
		LineTo(hDC, (int)m_vPoint[i].x + iScrollX, (int)m_vPoint[i].y);

	LineTo(hDC, (int)m_vPoint[0].x + iScrollX, (int)m_vPoint[0].y);

	DeleteObject(m_tPenInfo.OldPen);
	DeleteObject(m_tPenInfo.OldBrush);
}

void CBrick::Release(void)
{
}

void CBrick::Coll_Ev(CObj * _Obj)
{
	m_bRandSize = false;
}
