#include "stdafx.h"
#include "Stage1.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "MapMgr.h"

CStage1::CStage1()
	:m_dwTime(GetTickCount()), m_bSpike(false), m_bDead(false), m_iScore(0), m_bSuperMode(false)
{
}
	

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create());

	Add_Object(TEEMO, CAbstractFactory<CTeemo>::Create(300, 520));
	static_cast<CTeemo*>(Get_ObjList(TEEMO).front())->Set_TeemoState(2);
	MAPMGR->Initialize();
	MAPMGR->Manage_Pattern();
	__super::Initialize();
	LINE->Initialize();
	SOUND->PlayBGM(L"CatMario.wav", 0.3f);
}

int CStage1::Update()
{ 
	if (m_bSuperMode)
	{
		Delete_Object(SPIKE);
	}

	if (KEY->Key_Down('P'))
		m_bSuperMode = true;
	if (Get_ObjList(PLAYER).empty() && KEY->Key_Down('R'))
	{
		Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create());
		SCROLL->Scroll_Reset();
		Delete_Object(SPIKE);
		SOUND->StopSound(SOUND_BGM);
		SOUND->PlayBGM(L"CatMario.wav", 0.3f);
		m_iScore = 0;
		m_dwTime = GetTickCount();
		m_bSpike = false;
	}
	if (m_dwTime + 3000 < GetTickCount())
	{
		if (!m_bSpike)
		{
			for (int i = 0; i > -13; --i)
				Add_Object(SPIKE, CAbstractFactory<CSpike>::Create(0.f, 50.f * i + 25.f));
			for (int i = 1; i < 13; ++i)
				Add_Object(SPIKE, CAbstractFactory<CSpike>::Create(0.f, 50.f * i - 25.f));
			m_bSpike = true;
		}

	}
	
	__super::Update();
	LINE->Update();
	return 0;
}

void CStage1::Late_Update()
{
	__super::Late_Update();
	LINE->Late_Update();
}

void CStage1::Render(HDC hDC)
{
	HDC hBGDC = BITMAP->Find_Img(L"BG");
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hBGDC, -SCROLL->Get_ScrollX(), 0, WINCX, WINCY, SRCCOPY);
	__super::Render(hDC);
	LINE->Render(hDC);

	if (Get_ObjList(PLAYER).empty())
	{
		HDC hOverDC = BITMAP->Find_Img(L"Gameover");
		GdiTransparentBlt(hDC,
			0,100,
			WINCX, 240,
			hOverDC,
			0, 0,
			540, 140,
			RGB(100, 255, 255));

		TCHAR buf[32] = {};
		_itow_s(m_iScore, buf, 10); // hp값 int -> wstring
		HFONT hFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, TEXT("메이플스토리")); // 폰트변경
		HFONT oldFont = (HFONT)SelectObject(hDC, hFont); // DC관련
		SetTextAlign(hDC, TA_CENTER); // 텍스트 중앙정렬
		SetTextColor(hDC, RGB(255, 0, 255)); // 텍스트 컬러 설정
		SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
		TextOut(hDC, 400, 400, buf, lstrlen(buf));
		(HFONT)DeleteObject(oldFont);
	}
}
void CStage1::Release()
{
	__super::Release();
	LINE->Destroy_Instance();
	SOUND->Destroy_Instance();
	MAPMGR->Destroy_Instance();
}
