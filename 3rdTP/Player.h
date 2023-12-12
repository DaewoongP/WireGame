#pragma once
#include "Obj.h"
#include "Wire.h"
class CPlayer : public CObj
{
private:
	// isWired?, AngleSpeed, AngleAcc, Length, WirePoint
	struct WIREINFO
	{
		VERTEX		vWirePoint;
		bool		bWire;
		float		fLength;
		float		fAngleSpeed;
		float		fAngleAcc;		
	};
	// G, P, T
	struct JUMP
	{
		bool		bJump;
		float		fGravity;
		float		fPower;
		float		fTime;
	};
public:
	CPlayer();
	virtual ~CPlayer();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Coll_Ev(CObj * _Obj) override;
public:
	const float Get_PlayerSize(void) const { return m_fPlayerSize; }
	void		Set_Jump(bool _bJump) { m_tJump.bJump = _bJump; }
	const bool	Get_Jump(void)const { return m_tJump.bJump; }
private:
	void	Key_Input(void);
	void	Wiring();
	void	Check_Wire();
	void	Speed_Acc();
	void	OffSet(void);
private:
	const float m_fPlayerSize;
	WIREINFO	m_tWire;
	JUMP		m_tJump;

	VERTEX		m_vWireAcc;
};

