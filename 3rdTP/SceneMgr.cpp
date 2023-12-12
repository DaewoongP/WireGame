#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	:m_eCurScene(SC_STAGE1), m_ePreScene(SC_END), m_pScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;
	if (m_eCurScene != m_ePreScene)
	{		
		switch (eID)
		{
		case SC_STAGE1:
			Safe_Delete(m_pScene);
			m_pScene = new CStage1;
			break;
		default:
			break;
		}
		m_pScene->Initialize();
		
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	m_pScene->Delete_Object(PLAYER);
	Safe_Delete(m_pScene);
}

