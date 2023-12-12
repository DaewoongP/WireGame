#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_bDead(false), m_fSpeed(0.f), m_fAngle(0.f), m_PointIndex(0), m_dwTime(GetTickCount())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}


CObj::~CObj()
{
}

const D3DXVECTOR3 CObj::World_Trans(const D3DXVECTOR3 & _vec, bool _bAngleOption)
{
	// vLook 벡터 -> 기준 단위 벡터, vDir 벡터 -> 방향 단위 벡터
	MATRIX	matScale, matRotZ, matTrans;
	VERTEX	ReturnVec;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);
	if (_bAngleOption)
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	else
		D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	return *D3DXVec3TransformCoord(&ReturnVec, &_vec, &m_tInfo.matWorld);
}

const float CObj::Vector_Dot(D3DXVECTOR3 _Dir1, D3DXVECTOR3 _Dir2)
{
	// 단위 벡터의 내적을 통한 끼인각 계산
	D3DXVec3Normalize(&_Dir1, &_Dir1);
	D3DXVec3Normalize(&_Dir2, &_Dir2);
	float fInclude_Rad = acosf(D3DXVec3Dot(&_Dir1, &_Dir2));

	if (_Dir1.y < _Dir2.y)
		fInclude_Rad = 2 * D3DX_PI - fInclude_Rad;

	return fInclude_Rad;
}
