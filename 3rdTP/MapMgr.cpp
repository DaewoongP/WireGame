#include "stdafx.h"
#include "MapMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"

CMapMgr* CMapMgr::m_pInstance = nullptr;

CMapMgr::CMapMgr()
{
}


CMapMgr::~CMapMgr()
{
	Release();
}

void CMapMgr::Initialize()
{
	// ������ �⺻������ �ΰ����� ����. (�÷��̾ ó���� ���� ���ε� ����.) -> ���θŴ������� �׳� �ص� ����.
	SCENE->Get_Scene()->Add_Object(BRICK, CAbstractFactory<CBrick>::Create(600.f, 180.f));
	LINE->Add_Line({ -200.f, 300.f, 0.f }, {200.f, 300.f, 0.f});

	for (int i = 2; i < 100; i += 2)
	{
		LINE->Add_Line({ i * 1000.f, 500.f, 0.f }, {(i + 1) * 1000.f, 500.f, 0.f });
	}
	
	for (int i = 1; i < 100; ++i)
	{
		float k = 180.f;
		if (i % 3)
			k += 100.f;
		else
			k -= 100.f;
		SCENE->Get_Scene()->Add_Object(BRICK, CAbstractFactory<CBrick>::Create(400.f + (i * 800), k));
	}
}

void CMapMgr::Update()
{
}

void CMapMgr::Release()
{
}

void CMapMgr::Manage_Pattern()
{
	
}
