#include "stdafx.h"
#include "Wire.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

CWire::CWire()
{
	ZeroMemory(&m_tWire, sizeof(WIRE));
}


CWire::~CWire()
{
	Release();
}

void CWire::Initialize(void)
{
	m_tWire.vMouse = Get_Mouse();
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 1.f };
	// �÷��̾� �����ǰ� �����Ҷ� �ָ��.
	//m_tInfo.vPos
	World_Trans(m_tInfo.vPos, false);
	// Y��, �����ǿ��� Ÿ������ �����ϴ� ���� ���� 
	m_fAngle = Vector_Dot(m_tInfo.vLook, m_tWire.vMouse - m_tInfo.vPos);

	// ���콺��ġ�� -> ���� ����ȭ.
	m_tWire.vMouse.x = m_tWire.vMouse.x + (m_tWire.vMouse.y / tanf(m_fAngle));
	m_tWire.vMouse.y = 0.f;
}

int CWire::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Check_Wire();
	
	return OBJ_NOEVENT;
}

void CWire::Late_Update(void)
{
	int		iScrollX = (int)SCROLL->Get_ScrollX();

	if (m_tInfo.vPos.x < 0 - iScrollX ||
		m_tInfo.vPos.x > WINCX - iScrollX ||
		m_tInfo.vPos.y < 0 ||
		m_tInfo.vPos.y > WINCY)
		m_bDead = true;
}

void CWire::Render(HDC hDC)
{
	int		iScrollX = (int)SCROLL->Get_ScrollX();
	m_tPenInfo.CurPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	m_tPenInfo.CurBrush = CreateSolidBrush(RGB(0, 0, 0));
	m_tPenInfo.OldPen = (HPEN)SelectObject(hDC, m_tPenInfo.CurPen);
	m_tPenInfo.OldBrush = (HBRUSH)SelectObject(hDC, m_tPenInfo.CurBrush);

	MoveToEx(hDC,
		(int)SCENE->Get_Scene()->Get_Player()->Get_Info().vPos.x + iScrollX,
		(int)SCENE->Get_Scene()->Get_Player()->Get_Info().vPos.y, 
		nullptr);
	LineTo(hDC, 
		(int)m_tInfo.vPos.x + iScrollX,
		(int)m_tInfo.vPos.y);
	Ellipse(hDC,
		(int)m_tInfo.vPos.x - 5 + iScrollX,
		(int)m_tInfo.vPos.y - 5,
		(int)m_tInfo.vPos.x + 5 + iScrollX,
		(int)m_tInfo.vPos.y + 5);

	DeleteObject(m_tPenInfo.OldPen);
	DeleteObject(m_tPenInfo.OldBrush);
}

void CWire::Release(void)
{
}

void CWire::Coll_Ev(CObj * _Obj)
{
	if (!m_tWire.bWired)
		m_tWire.bWired = true;
}

const VERTEX CWire::Get_Mouse()
{
	int		iScrollX = (int)SCROLL->Get_ScrollX();
	POINT	Pt{};
	
	GetCursorPos(&Pt);	// ���콺 Ŀ���� ��ǥ���� ������ �Լ�
	ScreenToClient(g_hWnd, &Pt);
	VERTEX RetPt = {(float)Pt.x - iScrollX, (float)Pt.y, 0.f};
	return RetPt;
}

void CWire::Check_Wire()
{
	if (!m_tWire.bWired)
	{
		m_tInfo.vPos = {
			SCENE->Get_Scene()->Get_Player()->Get_Info().vPos.x + cosf(m_fAngle) * m_tWire.fLength,
			SCENE->Get_Scene()->Get_Player()->Get_Info().vPos.y - sinf(m_fAngle) * m_tWire.fLength,
			0.f
		};
		m_tWire.fLength += 15.f;
	}
}
