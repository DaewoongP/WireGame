#pragma once
#include "Obj.h"
class CBrick : public CObj
{
public:
	CBrick();
	virtual ~CBrick();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Coll_Ev(CObj * _Obj) override;

private:
	const float m_fBrickSize;
	bool		m_bRandSize;
};

