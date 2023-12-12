#pragma once
#include "Obj.h"
class CTeemo : public CObj
{
private:
	enum TEEMO
	{
		TEEMORIGHT,
		TEEMOUP,
		TEEMOEND
	};
public:
	CTeemo();
	virtual ~CTeemo();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Coll_Ev(CObj * _Obj) override;
public:
	// state 1 = right, state 2 = up
	void Set_TeemoState(int _State)
	{
		switch (_State)
		{
		case 1:
			m_eTeemoState = TEEMORIGHT;
			m_tInfo.vLook = { -1.f , 0.f , 0.f };
			break;
		case 2:
			m_eTeemoState = TEEMOUP;
			m_tInfo.vLook = { 1.f, 0.f, 0.f };
			
			break;
		default:
			return;
		}
	}
private:
	const float			m_fTeemoSize;
	TEEMO				m_eTeemoState;
	
};

