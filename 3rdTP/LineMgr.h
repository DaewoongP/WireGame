#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Add_Line(const VERTEX& _left, const VERTEX& _right);
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC _hDC);
	void		Release(void);
public:
	bool			Collision_Line(float& _fX, float* _pfY);
	list<CLine*>	Get_LineList(void) { return m_LineList; }
private:
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_LineList;
	MYPOINT					m_LinePoint[DIR_END];
public:
	static CLineMgr*	Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
};

#define LINE		CLineMgr::Get_Instance()