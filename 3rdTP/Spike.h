#pragma once
#include "Obj.h"
class CSpike : public CObj
{
public:
	CSpike();
	virtual ~CSpike();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Coll_Ev(CObj * _Obj) override;
public:
	// 스파이크 옵션 부여 (첫위치, 방향벡터, 스피드값, 각도) - 방향벡터는 단위벡터화
	void Set_SpikeOption(const VERTEX& _vPos, const VERTEX& _vLook, const float _fSpeed, const float _fAngle)
	{
		D3DXVec3Normalize(&m_tInfo.vLook, &_vLook);
		m_tInfo.vPos = _vPos;
		m_fSpeed = _fSpeed;
		m_fAngle = _fAngle;
	}

private:
	const float	m_fSpikeSize;
};

