#include "stdafx.h"
#include "Player.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	:m_fPlayerSize(30.f)
{
	ZeroMemory(m_vPoint, sizeof(VERTEX) * 4);
	ZeroMemory(m_vOriginPoint, sizeof(VERTEX) * 4);
	ZeroMemory(&m_tWire, sizeof(WIREINFO));
	ZeroMemory(&m_tJump, sizeof(JUMP));
	ZeroMemory(&m_vWireAcc, sizeof(VERTEX));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	// 포지션 설정
	m_tInfo.vPos = { 100.f, 50.f, 0.f };
	// 오른쪽 방향
	m_tInfo.vLook = { 1.f , 0.f , 0.f };
	// 플레이어 사이즈	 배율.
	m_tInfo.vSize = { 1.f ,1.f , 1.f };
	// 포인트 인덱스 명시
	m_PointIndex = 4;
	m_vPoint[0] = {-m_fPlayerSize,-m_fPlayerSize, 0.f };
	m_vPoint[1] = { m_fPlayerSize,-m_fPlayerSize, 0.f };
	m_vPoint[2] = { m_fPlayerSize, m_fPlayerSize, 0.f };
	m_vPoint[3] = {-m_fPlayerSize, m_fPlayerSize, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	// jump 초기화
	m_tJump.bJump = true;
	m_tJump.fGravity = 9.8f;
	m_tJump.fPower = 0.4f;
	m_tJump.fTime = 0.f;

	m_fAngle = D3DX_PI * 0.5f;
	m_fSpeed = 5.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
	{
		SOUND->StopSound(SOUND_BGM);
		SOUND->PlayBGM(L"DEAD.wav", 0.3f);
		static_cast<CStage1*>(SCENE->Get_Scene())->Set_Score((int)m_tInfo.vPos.x);
		return OBJ_DEAD;
	}
		
	Speed_Acc();

	// 와이어 타고있으면 SRT, 안타면 ST
	for (int i = 0; i < 4; ++i)
		m_vPoint[i] = World_Trans(m_vOriginPoint[i], m_tWire.bWire);

	Key_Input();
	Check_Wire();
	Wiring();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	OffSet();
	if (m_tInfo.vPos.y > WINCY)
	{
		SCENE->Get_Scene()->Delete_Object(WIRE);
		this->Set_Dead();
	}
	if (SCROLL->Get_ScrollX() > 28800)
		this->Set_Dead();
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)SCROLL->Get_ScrollX();

	m_tPenInfo.CurPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	m_tPenInfo.CurBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_tPenInfo.OldPen = (HPEN)SelectObject(hDC, m_tPenInfo.CurPen);
	m_tPenInfo.OldBrush = (HBRUSH)SelectObject(hDC, m_tPenInfo.CurBrush);
	

	MoveToEx(hDC, (int)m_vPoint[0].x + iScrollX,
		(int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
		LineTo(hDC, (int)m_vPoint[i].x + iScrollX,
			(int)m_vPoint[i].y);

	LineTo(hDC, (int)m_vPoint[0].x + iScrollX,
		(int)m_vPoint[0].y);


	if (m_vPoint[3].y < 0)
	{
		MoveToEx(hDC, (int)m_tInfo.vPos.x + iScrollX, 10, nullptr);
		LineTo(hDC, int(m_tInfo.vPos.x - m_fPlayerSize) + iScrollX, int(10 + m_fPlayerSize * sqrtf(3)));
		LineTo(hDC, int(m_tInfo.vPos.x + m_fPlayerSize) + iScrollX, int(10 + m_fPlayerSize * sqrtf(3)));
		LineTo(hDC, (int)m_tInfo.vPos.x + iScrollX, 10);
	}

	DeleteObject(m_tPenInfo.OldPen);
	DeleteObject(m_tPenInfo.OldBrush);

	TCHAR buf[32] = {};
	_itow_s((int)m_tInfo.vPos.x - 100, buf, 10); // hp값 int -> wstring
	HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("메이플스토리")); // 폰트변경
	HFONT oldFont = (HFONT)SelectObject(hDC, hFont); // DC관련
	SetTextAlign(hDC, TA_CENTER); // 텍스트 중앙정렬
	SetTextColor(hDC, RGB(255, 0, 255)); // 텍스트 컬러 설정
	SetBkMode(hDC, TRANSPARENT); // 매개변수 DC의 글자배경을 투명하게 한다. 
	TextOut(hDC, 150, 20, buf, lstrlen(buf));
	(HFONT)DeleteObject(oldFont);
}

void CPlayer::Release(void)
{
	SCENE->Get_Scene()->Delete_Object(WIRE);
	KEY->Destroy_Instance();
}

void CPlayer::Coll_Ev(CObj * _Obj)
{
}

void CPlayer::Wiring()
{
	if (m_tWire.bWire)
	{
		m_tJump.bJump = false;
							// (중력 / 질량)상수값 / 길이 * sinf(90 - 각도) -> 1,0,0 기준
		m_tWire.fAngleAcc = 0.4f / m_tWire.fLength * sinf(D3DX_PI * 0.5f - m_fAngle);
		m_tWire.fAngleSpeed += m_tWire.fAngleAcc;
		m_tWire.fAngleSpeed *= 0.995f;
		m_fAngle += m_tWire.fAngleSpeed;

		m_tInfo.vPos = 
		{
			m_tWire.vWirePoint.x - m_tWire.fLength * cosf(m_fAngle),
			m_tWire.vWirePoint.y + m_tWire.fLength * sinf(m_fAngle),
			0.f
		};
	}
	else if (m_tJump.bJump)
	{
		if (m_tJump.fPower * sinf(m_fAngle) * m_tJump.fTime
			- (m_tJump.fGravity * pow(m_tJump.fTime, 2.f) * 0.5f) < 0)
		{
			m_tJump.bJump = false;
			m_tInfo.vPos.y += m_tJump.fGravity;
			return;
		}
			
		m_tInfo.vPos =
		{
			m_tInfo.vPos.x += m_fSpeed * cosf(m_fAngle),
			// P * sin * t - 1/2 gt^2
			m_tInfo.vPos.y -= m_tJump.fPower * sinf(m_fAngle) * m_tJump.fTime
			- (m_tJump.fGravity * pow(m_tJump.fTime, 2.f) * 0.5f),
			m_tInfo.vPos.z
		};
		m_tJump.fTime += 0.1f;
	}
	else
	{
		m_tInfo.vPos.y += m_tJump.fGravity;
	}
}

void CPlayer::Check_Wire()
{
	if (SCENE->Get_Scene()->Get_Wire() != nullptr && 
		m_tWire.bWire == false &&
		static_cast<CWire*>(SCENE->Get_Scene()->Get_Wire())->Get_WireInfo().bWired)
	{
		m_tWire.bWire = true;
		m_tWire.vWirePoint = SCENE->Get_Scene()->Get_Wire()->Get_Info().vPos;
		m_fAngle = SCENE->Get_Scene()->Get_Wire()->Get_Angle();
		m_tWire.fLength = static_cast<CWire*>(SCENE->Get_Scene()->Get_Wire())->Get_WireInfo().fLength;
	}
}

void CPlayer::Speed_Acc()
{
	if (m_vWireAcc.x > 1.f)
		m_vWireAcc.x -= 1.f;
	else if (m_vWireAcc.x <= -1.f)
		m_vWireAcc.x += 1.f;
	else
		m_vWireAcc.x = 0.f;

	if (m_vWireAcc.y > 1.f)
		m_vWireAcc.y -= 0.5f;
	else if (m_vWireAcc.y <= -1.f)
		m_vWireAcc.y += 0.5f;
	else
		m_vWireAcc.y = 0.f;

	m_tInfo.vPos.x += m_vWireAcc.x;
	m_tInfo.vPos.y -= m_vWireAcc.y;
}

void CPlayer::Key_Input(void)
{
	if (KEY->Key_Down(VK_LBUTTON))
	{
		if (SCENE->Get_Scene()->Get_ObjList(WIRE).empty())
			SCENE->Get_Scene()->Add_Object(WIRE, CAbstractFactory<CWire>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y));
	}

	if (KEY->Key_Down(VK_SPACE))
	{
		if (m_tWire.bWire)
		{
			m_fAngle = D3DX_PI * 0.5f - m_fAngle;
			SCENE->Get_Scene()->Delete_Object(WIRE);
			m_vWireAcc.x += sinf(m_tWire.fAngleSpeed) * m_tWire.fLength * 2.5f;
			m_vWireAcc.y += cosf(m_tWire.fAngleSpeed) * m_tWire.fLength * 0.1f;
			
			ZeroMemory(&m_tWire, sizeof(WIREINFO));
			m_tJump.fTime = 0.f;
			m_tWire.bWire = false;
		}
		else if (!m_tJump.bJump)
		{
			m_fAngle = D3DX_PI * 0.5f;
			m_tJump.bJump = true;
			m_tJump.fPower = 10.f;
			m_tJump.fTime = 0.f;
		}
	}

	if (KEY->Key_Pressing('A'))
	{
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
		if (m_tWire.bWire)
			m_tWire.fAngleSpeed -= 0.0007f;
	}

	if (KEY->Key_Pressing('D'))
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		if (m_tWire.bWire)
			m_tWire.fAngleSpeed += 0.0007f;
	}
}

void CPlayer::OffSet(void)
{
	int		iOffSetminX = 100;
	int		iOffSetmaxX = 300;

	int		iScrollX = (int)SCROLL->Get_ScrollX();

	if (iOffSetmaxX < m_tInfo.vPos.x + iScrollX)
		SCROLL->Set_ScrollX(-m_fSpeed - m_vWireAcc.x);
	if (iOffSetminX > m_tInfo.vPos.x + iScrollX)
		SCROLL->Set_ScrollX(m_fSpeed - m_vWireAcc.x);
}