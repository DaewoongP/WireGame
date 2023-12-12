#pragma once
#include "Scene.h"
#include "Stage1.h"
#include "Include.h"

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();
public:
	void   Scene_Change(SCENEID eID);
	void   Update();
	void   Late_Update();
	void   Render(HDC hDC);
	void   Release();

	CScene*	Get_Scene() { return m_pScene; }
private:
	static CSceneMgr*       m_pInstance;
	CScene*					m_pScene;
	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;

public:
	static	CSceneMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}

	static void Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

};

#define SCENE		CSceneMgr::Get_Instance()