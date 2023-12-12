#include "stdafx.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Line(CObj * _Obj)
{
	if (LINE->Get_LineList().empty())
		return;
	if (static_cast<CPlayer*>(_Obj)->Get_Jump())
		return;

	CLine*		pTargetLine = nullptr;

	for (auto& iter : LINE->Get_LineList())
	{
		if (_Obj->Get_Info().vPos.x >= iter->Get_Info().tLPoint.fX &&
			_Obj->Get_Info().vPos.x <= iter->Get_Info().tRPoint.fX &&
			_Obj->Get_Info().vPos.y >= iter->Get_Info().tRPoint.fY - 50 &&
			_Obj->Get_Info().vPos.y <= iter->Get_Info().tRPoint.fY + 50)
			pTargetLine = iter;
	}

	if (nullptr == pTargetLine)
	{
		static_cast<CPlayer*>(_Obj)->Set_Jump(true);
		return;
	}
		

	// Y  = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float	x1 = pTargetLine->Get_Info().tLPoint.fX;
	float	y1 = pTargetLine->Get_Info().tLPoint.fY;

	float	x2 = pTargetLine->Get_Info().tRPoint.fX;
	float	y2 = pTargetLine->Get_Info().tRPoint.fY;

	_Obj->Set_LineY(
		((y2 - y1) / (x2 - x1)) * (_Obj->Get_Info().vPos.x - x1) + y1
		- static_cast<CPlayer*>(_Obj)->Get_PlayerSize());
	static_cast<CPlayer*>(_Obj)->Set_Jump(false);
}

void CCollisionMgr::Collision_Spike(CObj * _Player, list<CObj*> _Spike)
{
	for (auto& Spike : _Spike)
	{
		if (Check_Spike(_Player, Spike))
		{
			_Player->Set_Dead();
		}
	}
}

void CCollisionMgr::Collision_Wire(CObj * _Wire, list<CObj*> _Brick)
{
	for (auto& Brick : _Brick)
	{
		if (Check_Wire(_Wire, Brick))
		{
			_Wire->Coll_Ev(Brick);
			Brick->Coll_Ev(_Wire);
		}
	}
}

bool CCollisionMgr::Check_Wire(CObj * _Wire, CObj * _Brick)
{
	if (_Brick->Get_Point(0).x < _Wire->Get_Info().vPos.x &&
		_Brick->Get_Point(1).x > _Wire->Get_Info().vPos.x &&
		_Brick->Get_Point(0).y < _Wire->Get_Info().vPos.y &&
		_Brick->Get_Point(3).y > _Wire->Get_Info().vPos.y)
		return true;
	else
		return false;
}

bool CCollisionMgr::Check_Spike(CObj * _Player, CObj * _Spike)
{
	for (int i = 0; i < 3; ++i)
	{
		if (_Player->Get_Point(0).x < _Spike->Get_Point(i).x &&
			_Player->Get_Point(1).x > _Spike->Get_Point(i).x &&
			_Player->Get_Point(0).y < _Spike->Get_Point(i).y &&
			_Player->Get_Point(3).y > _Spike->Get_Point(i).y)
			return true;
	}
	return false;
}


#pragma region 사각형, 원 충돌처리
/*
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)
{
	float	fX = 0.f, fY = 0.f;


	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{

			if (Check_Rect(Dest, Src, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fY < Src->Get_Info().fY)
					{
						Dest->Set_Y(-fY);
					}
					else // 하 충돌
					{
						Dest->Set_Y(fY);
					}

				}
				else // 좌우 충돌
				{
					// 좌 충돌
					if (Dest->Get_Info().fX < Src->Get_Info().fX)
					{
						Dest->Set_X(-fX);
					}
					else // 우 충돌
					{
						Dest->Set_X(fX);
					}
				}

			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSrc)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDistance;
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSrc, float * pX, float * pY)
{
	float	fX = fabs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float	fY = fabs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float	fRadiusX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float	fRadiusY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fX) && (fRadiusY > fY))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;

		return true;
	}

	return false;
}
*/
#pragma endregion