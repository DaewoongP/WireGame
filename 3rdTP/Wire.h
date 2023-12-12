#pragma once
#include "Obj.h"
class CWire : public CObj
{
private:
	struct WIRE
	{
		VERTEX			vMouse;
		bool			bWired;
		float			fLength;
	};
public:
	CWire();
	virtual ~CWire();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Coll_Ev(CObj * _Obj) override;
public:
	const VERTEX		Get_Mouse();
	const WIRE& Get_WireInfo() { return m_tWire; }
	void Check_Wire();
private:
	WIRE			m_tWire;
};

