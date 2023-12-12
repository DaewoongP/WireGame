#pragma once
#include "Include.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual void		Initialize(void) PURE;
	virtual int			Update(void) PURE;
	virtual void		Late_Update(void) PURE;
	virtual void		Render(HDC hDC) PURE;
	virtual void		Release(void) PURE;
	virtual void		Coll_Ev(CObj* _Obj) PURE;
public:
	virtual const D3DXVECTOR3	World_Trans(const D3DXVECTOR3& _vec, bool _bAngleOption);
	virtual const float			Vector_Dot(D3DXVECTOR3 _Dir1, D3DXVECTOR3 _Dir2);

	const INFO	Get_Info(void) { return m_tInfo; }
	const float Get_Angle(void) { return m_fAngle; }
	void	Set_Pos(float _fX, float _fY) { m_tInfo.vPos.x = _fX; m_tInfo.vPos.y = _fY; }
	void	Set_LineY(float _fY) { m_tInfo.vPos.y = _fY; }
	void	Set_Dead() { m_bDead = true; }
	void	Set_Scale(const VERTEX& _vSize) { m_tInfo.vSize = _vSize; }
	const VERTEX&	Get_Point(const int _index)
	{
		if (_index > 0 || _index < m_PointIndex)
			return m_vPoint[_index];
		else
			return m_vPoint[m_PointIndex];
	}
	void	Set_Angle(float _Angle) { m_fAngle = _Angle; }
protected:
	INFO		m_tInfo;
	VERTEX		m_vPoint[10];
	VERTEX		m_vOriginPoint[10];
	DWORD		m_dwTime;
	int			m_PointIndex;
	float		m_fSpeed;
	bool		m_bDead;
	float		m_fAngle;

	PENINFO		m_tPenInfo;
};

