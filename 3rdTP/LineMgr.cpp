#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
	ZeroMemory(m_LinePoint, sizeof(m_LinePoint));
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Add_Line(const VERTEX& _left, const VERTEX& _right)
{
	MYPOINT		Left, Right;
	Left = { _left.x, _left.y };
	Right = { _right.x, _right.y };
	m_LineList.push_back(new CLine(Left, Right));
}

void CLineMgr::Initialize(void)
{
}

int CLineMgr::Update(void)
{
	return 0;
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC _hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(_hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
	SCROLL->Destroy_Instance();
	KEY->Destroy_Instance();
}

bool CLineMgr::Collision_Line(float& _fX, float* _pfY)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
			pTargetLine = iter;
	}

	if (nullptr == pTargetLine)
		return false;
	
	// Y  = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float	x1 = pTargetLine->Get_Info().tLPoint.fX;
	float	y1 = pTargetLine->Get_Info().tLPoint.fY;
	
	float	x2 = pTargetLine->Get_Info().tRPoint.fX;
	float	y2 = pTargetLine->Get_Info().tRPoint.fY;

	*_pfY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}