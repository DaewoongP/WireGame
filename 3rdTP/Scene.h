#pragma once
#include "Include.h"
#include "Obj.h"
#include "Player.h"
#include "Brick.h"
#include "Spike.h"
#include "Teemo.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual void	Initialize();
	virtual int		Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void	Release();
public:
	void Add_Object(OBJID eID, CObj * pObj);
	void Delete_Object(OBJID eID);
public:
	CObj* Get_Player()
	{
		if (!m_ObjList[PLAYER].empty())
			return m_ObjList[PLAYER].front();
		else
			return nullptr;
	}
	CObj* Get_Wire()
	{
		if (!m_ObjList[WIRE].empty())
			return m_ObjList[WIRE].front();
		else
			return nullptr;
	}
	list<CObj*> Get_ObjList(OBJID _ObjID) { return m_ObjList[_ObjID]; }

protected:
	list<CObj*>			m_ObjList[OBJ_END];
	list<CObj*>			m_RenderList[OBJ_END];

	DWORD				m_dwTime;
};	

