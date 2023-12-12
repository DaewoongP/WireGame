#include "stdafx.h"
#include "Scene.h"
#include "CollisionMgr.h"
CScene::CScene()
{
}


CScene::~CScene()
{
	Release();
}

void CScene::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CScene::Delete_Object(OBJID eID)
{
	for_each(m_ObjList[eID].begin(), m_ObjList[eID].end(), Safe_Delete<CObj*>);
	m_ObjList[eID].clear();
}


void CScene::Initialize()
{
	for (size_t i = PLAYER; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
		iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Initialize();
		}
	}
}

int CScene::Update()
{
	srand(unsigned(time(NULL)));
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
		iter != m_ObjList[i].end();)
		{
			int iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return 0;
}

void CScene::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
		iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Late_Update();

			if (m_ObjList[i].empty())
				break;
		}
	}
	if (!m_ObjList[PLAYER].empty())
	{
		COLL::Collision_Line(m_ObjList[PLAYER].front());
		COLL::Collision_Spike(m_ObjList[PLAYER].front(), m_ObjList[SPIKE]);
	}
		
	if (!m_ObjList[WIRE].empty())
		COLL::Collision_Wire(m_ObjList[WIRE].front(), m_ObjList[BRICK]);
}

void CScene::Render(HDC hDC)
{
	for (size_t i = PLAYER; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
		iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Render(hDC);
		}
	}
}

void CScene::Release()
{
	for (size_t i = PLAYER; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

