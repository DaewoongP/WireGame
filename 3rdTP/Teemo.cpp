#include "stdafx.h"
#include "Teemo.h"
#include "ScrollMgr.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"

CTeemo::CTeemo()
	:m_fTeemoSize(30.f)
{
}


CTeemo::~CTeemo()
{
	Release();
}

void CTeemo::Initialize(void)
{
	m_tInfo.vSize = { 1.f, 1.f, 1.f };
	m_PointIndex = 0;

	// 스파이크 스피드
	m_fSpeed = 10.f;
}

int CTeemo::Update(void)
{
	if (m_dwTime + 1500 < GetTickCount())
	{
		SCENE->Get_Scene()->Add_Object(SPIKE, CAbstractFactory<CSpike>::Create());
		static_cast<CSpike*>(SCENE->Get_Scene()->Get_ObjList(SPIKE).back())->Set_SpikeOption(
			{m_tInfo.vPos.x - SCROLL->Get_ScrollX(),
			m_tInfo.vPos.y,
			m_tInfo.vPos.z
			},
			m_tInfo.vLook, abs(m_fSpeed), D3DX_PI * 1.5f);

		m_dwTime = GetTickCount();
	}
	
	if (m_tInfo.vPos.x < 100 || m_tInfo.vPos.x > 700)
		m_fSpeed *= -1;
	m_tInfo.vPos.x += m_fSpeed;
	
	return OBJ_NOEVENT;
}

void CTeemo::Late_Update(void)
{
}

void CTeemo::Render(HDC hDC)
{
	HDC hMemDC;
	switch (m_eTeemoState)
	{
	case TEEMORIGHT:
		hMemDC = BITMAP->Find_Img(L"TeemoRight");
		GdiTransparentBlt(hDC,
			int(m_tInfo.vPos.x - m_fTeemoSize),
			int(m_tInfo.vPos.y - m_fTeemoSize),
			int(m_fTeemoSize), // 키울 사이즈
			int(m_fTeemoSize),
			hMemDC,
			0,
			0,
			500,		// 텍스처 원본 사이즈
			250,
			RGB(100, 255, 255));
		break;
	case TEEMOUP:
		hMemDC = BITMAP->Find_Img(L"TeemoUp");
		GdiTransparentBlt(hDC,
			int(m_tInfo.vPos.x),
			int(m_tInfo.vPos.y),
			50, // 키울 사이즈
			100,
			hMemDC,
			0,
			0,
			200,		// 텍스처 원본 사이즈
			420,
			RGB(100, 255, 255));
		break;
	}
	

}

void CTeemo::Release(void)
{
}

void CTeemo::Coll_Ev(CObj * _Obj)
{
}
