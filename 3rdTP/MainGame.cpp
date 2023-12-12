#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "BitmapMgr.h"
#include "SoundMgr.h"
CMainGame::CMainGame()
	:m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	SOUND->Initialize();
	BitMap_Init();

	SCENE->Scene_Change(SC_STAGE1);
}

void CMainGame::Update(void)
{
	DWORD dwExitCode = 0;
	SCENE->Update();
}

void CMainGame::Late_Update(void)
{
	SCENE->Late_Update();
}

void CMainGame::Render(void)
{
	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	HDC	hBackDC = BITMAP->Find_Img(L"Back");
	SCENE->Render(hBackDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	
}

void CMainGame::Release(void)
{
	SCENE->Destroy_Instance();
	BITMAP->Destroy_Instance();
}

void CMainGame::BitMap_Init()
{
	BITMAP->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	BITMAP->Insert_Bmp(L"../Image/BG.bmp", L"BG");
	BITMAP->Insert_Bmp(L"../Image/Gameover.bmp", L"Gameover");
	BITMAP->Insert_Bmp(L"../Image/TeemoRight.bmp", L"TeemoRight");
	BITMAP->Insert_Bmp(L"../Image/TeemoUp.bmp", L"TeemoUp");
}
