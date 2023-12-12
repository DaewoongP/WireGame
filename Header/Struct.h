#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	D3DXVECTOR3		vSize;

	D3DXMATRIX		matWorld;
}INFO;

typedef		struct tagTexture
{
	LPDIRECT3DTEXTURE9	pTexture;	// ��ü, �̹����� ���õ� ���� ����� �����ϴ� Ŭ����

	D3DXIMAGE_INFO		tImgInfo;	// ����ü, �̹����� ���õ� �������� �����͸� �����ϴ� ����ü

}TEXINFO;


typedef struct tagTile
{
	D3DXVECTOR3	vPos;
	D3DXVECTOR3	vSize;
	BYTE		byOption;
	BYTE		byDrawID;

	int			iIndex = 0;
	int			iParentIdx = 0;

}TILE;

typedef struct tagUnitData
{

#ifndef _AFX
	wstring		strName;
#else
	CString		strName;
#endif // !_AFX
	
	int			iAttack;
	int			iHp;
	BYTE		byJobIndex;
	BYTE		byItem;
	
}UNITDATA;


static D3DXVECTOR3		Get_Mouse()
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}


typedef	struct tagTexturePath
{
	wstring			wstrObjKey		= L"";
	wstring			wstrStateKey	= L"";
	wstring			wstrPath		= L"";
	int				iCount			= 0;

}IMGPATH;

typedef	struct tagFrame
{
	float	fFrame;	// ���� �ִϸ��̼� ��� ����
	float	fMax;	// �ִ� �ִϸ��̼� ����

}FRAME;

typedef struct tagSoundInfo
{
	TCHAR*	szName;
	CHANNELID eID;
	float	fVolume;

}SOUNDINFO;


typedef		struct tagLinePoint
{
	float	fX;
	float	fY;

	tagLinePoint(void) { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}MYPOINT;

typedef	struct tagLine
{
	MYPOINT		tLPoint;
	MYPOINT		tRPoint;

	tagLine(void) { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(MYPOINT& tLeft, MYPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight) {}

}LINE;

struct PENINFO
{
	HPEN	CurPen;
	HBRUSH	CurBrush;
	HPEN	OldPen;
	HBRUSH	OldBrush;
};