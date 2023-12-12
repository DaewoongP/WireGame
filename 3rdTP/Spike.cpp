#include "stdafx.h"
#include "Spike.h"
#include "ScrollMgr.h"

CSpike::CSpike()
	:m_fSpikeSize(50.f)
{
}


CSpike::~CSpike()
{
	Release();
}

void CSpike::Initialize(void)
{
	m_tInfo.vLook = { 1.f , 0.f , 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 1.f };
	m_PointIndex = 3;
	m_vPoint[0] = { m_fSpikeSize * sqrtf(3) * 0.5f, 0.f, 0.f };
	m_vPoint[1] = { 0.f, -m_fSpikeSize * 0.5f, 0.f };
	m_vPoint[2] = { 0.f,  m_fSpikeSize * 0.5f, 0.f };

	for (int i = 0; i < 3; ++i)
		m_vOriginPoint[i] = m_vPoint[i];
	m_fSpeed = 3.f;
}

int CSpike::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_dwTime + 1000 < GetTickCount())
	{
		++m_fSpeed;
		m_dwTime = GetTickCount();
	}
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	for (int i = 0; i < 3; ++i)
		m_vPoint[i] = World_Trans(m_vOriginPoint[i], false);

	if (m_fAngle)
	{
		for (int i = 0; i < 3; ++i)
			m_vPoint[i] = World_Trans(m_vOriginPoint[i], true);
	}
		
	return OBJ_NOEVENT;
}

void CSpike::Late_Update(void)
{
	if (m_vPoint[1].y < -1000)
		this->Set_Dead();
}

void CSpike::Render(HDC hDC)
{
	int		iScrollX = (int)SCROLL->Get_ScrollX();
	m_tPenInfo.CurPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	m_tPenInfo.CurBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_tPenInfo.OldPen = (HPEN)SelectObject(hDC, m_tPenInfo.CurPen);
	m_tPenInfo.OldBrush = (HBRUSH)SelectObject(hDC, m_tPenInfo.CurBrush);
	
	MoveToEx(hDC, (int)m_vPoint[0].x + iScrollX,
		(int)m_vPoint[0].y, nullptr);
	for (int i = 0; i < 3; ++i)
		LineTo(hDC, (int)m_vPoint[i].x + iScrollX, (int)m_vPoint[i].y);
	LineTo(hDC, (int)m_vPoint[0].x + iScrollX, (int)m_vPoint[0].y);

	DeleteObject(m_tPenInfo.OldPen);
	DeleteObject(m_tPenInfo.OldBrush);
}

void CSpike::Release(void)
{
}

void CSpike::Coll_Ev(CObj * _Obj)
{
}

