#pragma once
#include "Brick.h"
class CMapMgr
{
private:
	enum PATTERNTYPE { TYPE_A, TYPE_B, TYPE_END };
public:
	CMapMgr();
	~CMapMgr();
public:
	void		Initialize();
	void		Update();
	void		Release();
	void		Manage_Pattern();

private:
	static CMapMgr*			m_pInstance;
	vector<list<CObj*>>		m_PatternList;
public:
	static	CMapMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CMapMgr;
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

#define		MAPMGR		CMapMgr::Get_Instance()