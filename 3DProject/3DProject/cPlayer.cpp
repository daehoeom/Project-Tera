#include "stdafx.h"
#include "cPlayer.h"
#include "cBody.h"
#include "cHair.h"
#include "cFace.h"
#include "cTail.h"
#include "cWeaponMesh.h"
#include "cBoundingSphere.h"
#include "cBoundingBox.h"

cPlayer::cPlayer( ) :
	cCollisionObject( "Player" )
	, m_vDirection(D3DXVECTOR3(0, 0, 1))
	, m_fSpeed(1.f)
	, m_fAngle(0.f)
	, m_fPassTime(0.f)
	, m_fPeriod(0.f)
	, m_bAlive(true)
	, m_bIsAction(false)
	, m_bPushBehind(false)
	, m_pCombo(nullptr)
	, n(0)
{
	SetPlayerState(PLAYER_BATTLEIDLE);

	//대기상태
	m_pBody = new cBody;
	m_pBody->Setup("CH/Player", "Player_Body.X");

	m_pFace = new cFace;
	m_pFace->SetNeckTM(&m_pBody->GetNeckTM());
	m_pFace->Setup("CH/Player", "Player_Head.X");

	m_pHair = new cHair;
	m_pHair->SetHairTM(&m_pBody->GetHairTM());
	m_pHair->Setup("CH/Player", "Player_Hair.X");

	m_pTail = new cTail;
	m_pTail->SetTailTM(&m_pBody->GetTailTM());
	m_pTail->Setup("CH/Player", "Player_Tail.X");

	m_pHand = new cWeaponMesh;
	m_pHand->SetWeapon(&m_pBody->GetWeaponBack());
	m_pHand->Setup("CH/Player", "Lance.X");

	//콤보 클래스
	m_pCombo = new cCommandCombo;

	//몸통 충돌체
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 9.f));
	D3DXMATRIXA16 matLocal;
	D3DXMatrixTranslation(&matLocal, 0, 15, 0);
	this->GetColliderRepo()[0]->SetLocal(&matLocal);
	D3DXVECTOR3 vPos(GetPosition().x + matLocal._41, GetPosition().y + matLocal._42, GetPosition().z + matLocal._43);
	this->GetColliderRepo()[0]->SetPosition(vPos);

	//무기 충돌체

	SetAniTrack(PLAYER_BATTLEIDLE);
	this->SetCollisionType(CollisionType::ePlayer);
}

cPlayer::~cPlayer( )
{
	SAFE_DELETE(m_pBody);
	SAFE_DELETE(m_pHair);
	SAFE_DELETE(m_pFace);
	SAFE_DELETE(m_pTail);
	SAFE_DELETE(m_pHand);
}

void cPlayer::Update( )
{
	__super::Update( );

	SetUpdateState();

	this->GetColliderRepo()[0]->SetWorld(&m_matWorld);
	
	if (this->IsActive())
	{
		KeyControl();
	}

	SetFSMState();

	m_pCombo->Update();

	if (this->GetCurrHp() <= 0 && this->IsActive() && GetPlayerState() != PLAYER_DEATH)
	{
		m_bIsAction = false;
		SetPlayerState(PLAYER_DEATH);
	}
}

void cPlayer::Render( )
{
	__super::Render( );

	SetRenderState();
}

void cPlayer::KeyControl()
{
	D3DXMATRIXA16 matR, matT;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_fAngle -= 0.1f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_fAngle += 0.1f;
	}

	m_vDirection = D3DXVECTOR3(1, 0, 0);
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//달리기보다 우선순위가 뒤인 행동을 하고 있을 경우 그 행동의 메시지 취소
		if (GetPlayerState() == PLAYER_BATTLEIDLE)
		{
			m_bIsAction = false;
		}

		//우선순위가 높은 행동일 땐 행동변경 불가
		if (GetPlayerState() == PLAYER_TUMBLING || GetPlayerState() == PLAYER_SKILL1 || GetPlayerState() == PLAYER_SKILL2 ||
			GetPlayerState() == PLAYER_SKILL3 || GetPlayerState() == PLAYER_SKILL4 || GetPlayerState() == PLAYER_COMBO1 ||
			GetPlayerState() == PLAYER_COMBO2 || GetPlayerState() == PLAYER_COMBO3 || GetPlayerState() == PLAYER_COMBO4)
		{
			m_bIsAction = true;
		}

		else 
		{
			SetPlayerState(PLAYER_RUN);
			SetPosition(GetPosition() + m_vDirection * m_fSpeed);
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		SetPlayerState(PLAYER_BATTLEIDLE);
		SetAniTrack(PLAYER_BATTLEIDLE);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//달리기보다 우선순위가 뒤인 행동을 하고 있을 경우 그 행동의 메시지 취소
		if (GetPlayerState() == PLAYER_BATTLEIDLE)
		{
			m_bIsAction = false;
		}

		//우선순위가 높은 행동일 땐 행동변경 불가
		if (GetPlayerState() == PLAYER_TUMBLING || GetPlayerState() == PLAYER_SKILL1 || GetPlayerState() == PLAYER_SKILL2 ||
			GetPlayerState() == PLAYER_SKILL3 || GetPlayerState() == PLAYER_SKILL4 || GetPlayerState() == PLAYER_COMBO1 || 
			GetPlayerState() == PLAYER_COMBO2 || GetPlayerState() == PLAYER_COMBO3 || GetPlayerState() == PLAYER_COMBO4)
		{
			m_bIsAction = true;
		}

		else 
		{
			SetPlayerState(PLAYER_RUN);
			SetPosition(GetPosition() + m_vDirection * m_fSpeed);
		}

		//방향키 뒤를 눌렀을 때 한번만 뒤를 볼 것
		if (!m_bPushBehind)
		{
			m_fAngle = m_fAngle - D3DX_PI;
			m_bPushBehind = true;
			int a = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		SetPlayerState(PLAYER_BATTLEIDLE);

		if (m_bPushBehind)
		{
			m_bPushBehind = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (m_bIsAction)
		{
			if (GetPlayerState() == PLAYER_RUN || GetPlayerState() == PLAYER_BATTLEIDLE)
				m_bIsAction = false;
		}

		if (GetPlayerState() != PLAYER_COMBO1 || GetPlayerState() != PLAYER_COMBO2 ||
			GetPlayerState() != PLAYER_COMBO3 || GetPlayerState() != PLAYER_COMBO4)
		{
			SetPlayerState(PLAYER_COMBO1);
		}

		//평타를 한번도 하지 않았다면?
		if (m_pCombo->GetCommand().size() == 0)
		{
			m_pCombo->Input(m_pBody->GetAniTrackPeriod(PLAYER_COMBO1));
		}

		else if (m_pCombo->GetCommand().size() == 1)
		{
			m_pCombo->Input(m_pBody->GetAniTrackPeriod(PLAYER_COMBO2));
		}

		else if (m_pCombo->GetCommand().size() == 2)
		{
			m_pCombo->Input(m_pBody->GetAniTrackPeriod(PLAYER_COMBO3));
		}

		else if (m_pCombo->GetCommand().size() == 3)
		{
			m_pCombo->Input(m_pBody->GetAniTrackPeriod(PLAYER_COMBO4));
		}
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		//텀블링은 모든 행동에 대해서 우선순위가 가장 높다.
		if (m_bIsAction)
		{
			m_bIsAction = false;
		}

		//평타 콤보 취소
		m_pCombo->Destroy();
		SetPlayerState(PLAYER_TUMBLING);
	}

	//스킬 행동 중일땐 텀블링 이외에는 캔슬할 수 없다.
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (GetPlayerState() != PLAYER_TUMBLING && GetPlayerState() != PLAYER_SKILL2 && 
			GetPlayerState() != PLAYER_SKILL3 && GetPlayerState() != PLAYER_SKILL4)
		{
			m_bIsAction = false;
		}

		if (GetPlayerState() == PLAYER_SKILL1)
		{
			m_bIsAction = true;
		}

		//평타 콤보 취소
		m_pCombo->Destroy();
		SetPlayerState(PLAYER_SKILL1);
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (GetPlayerState() != PLAYER_TUMBLING && GetPlayerState() != PLAYER_SKILL1 && 
			GetPlayerState() != PLAYER_SKILL3 && GetPlayerState() != PLAYER_SKILL4)
		{
			m_bIsAction = false;
		}

		//실행 중일땐 취소 불가
		if (GetPlayerState() == PLAYER_SKILL2)
		{
			m_bIsAction = true;
		}

		//평타 콤보 취소
		m_pCombo->Destroy();
		SetPlayerState(PLAYER_SKILL2);
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (GetPlayerState() != PLAYER_TUMBLING && GetPlayerState() != PLAYER_SKILL1 &&
			GetPlayerState() != PLAYER_SKILL2 && GetPlayerState() != PLAYER_SKILL4)
		{
			m_bIsAction = false;
		}

		if (GetPlayerState() == PLAYER_SKILL3)
		{
			m_bIsAction = true;
		}

		//평타 콤보 취소
		m_pCombo->Destroy();
		SetPlayerState(PLAYER_SKILL3);
	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		if (GetPlayerState() != PLAYER_TUMBLING && GetPlayerState() != PLAYER_SKILL1 &&
			GetPlayerState() != PLAYER_SKILL2 && GetPlayerState() != PLAYER_SKILL3)
		{
			m_bIsAction = false;
		}

		if (GetPlayerState() == PLAYER_SKILL4)
		{
			m_bIsAction = true;
		}

		//평타 콤보 취소
		m_pCombo->Destroy();
		SetPlayerState(PLAYER_SKILL4);
	}

	D3DXMatrixTranslation(&matT, GetPosition().x, GetPosition().y - 4.f, GetPosition().z);
	m_matWorld = matR * matT;
}

void cPlayer::OnCollisionStay(cCollisionObject* rhs)
{
	//한번만 충돌체크하게
	if (rhs->GetCollisionType() == CollisionType::eBuilding && !this->GetCollision())
	{
		this->SetCollision(true);
	}

	if (rhs->GetCollisionType() == CollisionType::eMonster && !this->GetCollision())
	{
		this->SetCollision(true);
		rhs->SetCurrHp(rhs->GetCurrHp() - 100);
		int a = 0;
	}
}

void cPlayer::SetFSMState()
{
	switch (GetPlayerState())
	{
	case PLAYER_BATTLEIDLE:
	{
		if (!m_bIsAction)
		{
			SetAniTrack(PLAYER_BATTLEIDLE);
			m_bIsAction = true;
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_BATTLEIDLE) ;
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
	}
		break;

	case PLAYER_RUN:
	{
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_RUN);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_RUN);
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
	}
		break;

	case PLAYER_COMBO1:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_COMBO1);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_COMBO1) + 0.27f;
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				if (m_pCombo->GetCommand().size() > 1)
					SetPlayerState(PLAYER_COMBO2);

				else if (m_pCombo->GetCommand().size() <= 1)
					SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

	case PLAYER_COMBO2:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_COMBO2);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_COMBO2) + 0.35f;
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;

				if (m_pCombo->GetCommand().size() > 2)
					SetPlayerState(PLAYER_COMBO3);

				else if (m_pCombo->GetCommand().size() <= 2)
					SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

	case PLAYER_COMBO3:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_COMBO3);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_COMBO3) + 0.19f;
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				if (m_pCombo->GetCommand().size() > 3)
					SetPlayerState(PLAYER_COMBO4);

				if (m_pCombo->GetCommand().size() <= 3)
					SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

	case PLAYER_COMBO4:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_COMBO4);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_COMBO4) + 0.19f;
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;
	
	case PLAYER_TUMBLING:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_TUMBLING);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_TUMBLING);
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime < m_fPeriod - 0.75f)
			{
				SetPosition(GetPosition() + m_vDirection * (m_fPeriod - 1));
			}

			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

		//강하게 내려치기
	case PLAYER_SKILL1:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_SKILL1);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_SKILL1);
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime < m_fPeriod - 1.0f)
			{
				SetPosition(GetPosition() + m_vDirection * (m_fPeriod - 1.f));
			}

			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

		//슬래쉬
	case PLAYER_SKILL2:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_SKILL2);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_SKILL2);
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

		//강하게 옆으로찍기
	case PLAYER_SKILL3:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_SKILL3);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_SKILL3);
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

		//회오리 치기
	case PLAYER_SKILL4:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_SKILL4);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_SKILL4);
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetPlayerState(PLAYER_BATTLEIDLE);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

	case PLAYER_DEATH:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_DEATH);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_DEATH) - 0.2f;
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetPlayerState(PLAYER_DEATHWAIT);
				this->SetActive(false);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y - 0.08f, GetPosition().z));
				m_fPassTime += g_pTimeManager->GetDeltaTime() / fAniTime;
			}
		}
		break;

	case PLAYER_DEATHWAIT:
		if (!m_bIsAction)
		{
			m_bIsAction = true;
			SetAniTrack(PLAYER_DEATHWAIT);
			m_fPeriod = m_pBody->GetAniTrackPeriod(PLAYER_DEATHWAIT);
		}
		break;
	}
}

void cPlayer::SetUpdateState( )
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}
	if (m_pHair)
	{
		m_pHair->SetHairTM(&m_pBody->GetHairTM());
		m_pHair->Update();
	}
	if (m_pFace)
	{
		m_pFace->SetNeckTM(&m_pBody->GetNeckTM());
		m_pFace->Update();
	}

	if (m_pTail)
	{
		m_pTail->SetTailTM(&m_pBody->GetTailTM());
		m_pTail->Update();
	}

	if (m_pHand)
	{
		m_pHand->SetWeapon(&m_pBody->GetWeaponHand());
		m_pHand->Update();
	}
}

void cPlayer::SetRenderState()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
	if (m_pHair)
	{
		m_pHair->Render();
	}
	if (m_pFace)
	{
		m_pFace->Render();
	}

	if (m_pTail)
	{
		m_pTail->Render();
	}

	if (m_pHand)
	{
		m_pHand->Render(NULL);
	}
}

void cPlayer::SetAniTrack(int nIndex)
{
	m_pBody->SetAnimationIndex(nIndex);
	m_pHair->SetAnimationIndex(nIndex);
	m_pFace->SetAnimationIndex(nIndex);
	m_pTail->SetAnimationIndex(nIndex);
}