#pragma once
#include "Obj.h"
#include "Player.h"
#include "Brick.h"
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void Collision_Line(CObj* _Obj);
	static void Collision_Spike(CObj* _Player, list<CObj*> _Spike);
	static void Collision_Wire(CObj* _Wire, list<CObj*> _Brick);
	static bool Check_Wire(CObj* _Wire, CObj* _Brick);
	static bool Check_Spike(CObj* _Player, CObj* _Spike);

#pragma region 사각형, 원 충돌처리
	/*
	static void Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src) {}
	static void Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src) {}

	static bool Check_Sphere(CObj* pDest, CObj* pSrc) {}
	static bool Check_Rect(CObj* pDest, CObj* pSrc, float* pX, float* pY) {}
	*/
#pragma endregion
};

#define		COLL		CCollisionMgr