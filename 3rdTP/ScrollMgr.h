#pragma once
#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float	Get_ScrollX(void) { return m_fScrollX; }
	void	Set_ScrollX(float _fX) { m_fScrollX += _fX; }

	float	Get_ScrollY(void) { return m_fScrollY; }
	void	Set_ScrollY(float _fY) { m_fScrollY += _fY; }

	void	Scroll_Reset() { m_fScrollX = 0; m_fScrollY = 0; }
public:
	static CScrollMgr*	Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;

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

public:
	void		Scroll_Lock(void);

private:
	static CScrollMgr*		m_pInstance;
	float					m_fScrollX;
	float					m_fScrollY;
};

#define SCROLL		CScrollMgr::Get_Instance()