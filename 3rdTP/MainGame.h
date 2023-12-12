#pragma once
#include "Include.h"
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void		Initialize(void);
	void		Update(void);	// �� �����Ӹ��� ��ǥ ��ȯ�� ���õ� �ڵ带 �����ϴ� �Լ�
	void		Late_Update(void);
	void		Render(void);	// �� �����Ӹ��� �׸��� �ڵ带 ȣ���ϴ� �Լ�
	void		Release(void);

	void		BitMap_Init();
private:
	HDC				m_hDC;
	DWORD			m_dwTime;

	TCHAR			m_szFPS[32];
	int				m_iFPS;
};

