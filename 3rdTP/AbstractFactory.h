#pragma once
#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*	Create()
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj*	Create(float _fX, float _fY)
	{
		CObj*	pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();
		return pObj;
	}

};