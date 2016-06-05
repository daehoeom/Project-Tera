#include "stdafx.h"
#include "cEnemy.h"
#include "cEnemySkinMesh.h"


cEnemy::cEnemy()
	:cCollisionObject("monster")
	, m_pBody(nullptr)
	, m_nMaxHp(1000)
	, m_nCurrentHp(1000)
	, n(0)
	, m_fSpeed(0.5f)
	, m_fAngle(0.f)
	, m_sState(ENEMY_RUN)
	, m_bIsAction(false)
	, m_vOrigin(0, 0, 0)
	, m_vPosition(0, 0, 0)
	, m_vDirection(1, 0, 0)
	, m_bAlive(true)
{
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&matT);
}


cEnemy::~cEnemy()
{
}

void cEnemy::Update()
{
	__super::Update();

	//몬스터가 움직일 수 있는 일정 범위
	float Length = D3DXVec3Length(&(m_vPosition - m_vOrigin));

	//몬스터와 플레이어의 사이 거리 
	float Distance = D3DXVec3Length(&(m_vPosition - g_player->GetPosition()));

	//몬스터의 HP가 0인데 아직 죽음 처리가 안되었다면
	if (m_nCurrentHp < 0.f && m_bAlive)
	{
		m_sState = ENEMY_DEATH;
		
		//실행 중인 행동을 중지하고 현재상태의 행동을 할 것
		m_bIsAction = false;
	}

	//몬스터가 일정 범위를 넘어가면 다시 되돌아 올 것
	else if (abs(Length) > 300.f && m_bAlive)
	{
		m_sState = ENEMY_BACKPOSITION;

		//실행 중인 행동을 중지하고 현재상태의 행동을 할 것
		m_bIsAction = false;

	}

	//만약 몬스터의 상태가 되돌아가기가 아니라면 플레이어 쫒기
	else if (abs(Distance) < 100.f && m_bAlive && m_sState != ENEMY_BACKPOSITION)
	{
		m_sState = ENEMY_CHASE;

		//실행 중인 행동을 중지하고 현재상태의 행동을 할 것
		m_bIsAction = false;
	}

	ActionState();

	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}
}

void cEnemy::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}

void cEnemy::ActionState()
{
	switch (m_sState)
	{
	case ENEMY_IDLE:
	{
		//이 행동에 대한 메시지를 방금 받았으면
		if (!m_bIsAction)
		{
			m_pBody->SetAnimationIndex(ENEMY_IDLE);
			m_bIsAction = true;
			m_fPeriod = 2.f;
		}

		//모든 대기시간이 종료되면 순찰하기로 돌아간다.
		if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_fPeriod = 0.f;
				m_fPassTime = 0.f;
				m_sState = ENEMY_RUN;
				m_bIsAction = false;
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime();
			}
		}

		int a = 0;
	}

	break;
	case ENEMY_DEATH:
	{
		//이 행동에 대한 메시지를 방금 받았으면
		if (!m_bIsAction)
		{
			m_pBody->SetAnimationIndex(ENEMY_DEATH);
			m_bIsAction = true;
			m_fPeriod = m_pBody->GetAniTrackPeriod(3) - 0.25f;
		}

		if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				m_sState = ENEMY_DEATHWAIT;

				//모든 죽음 처리가 다 끝났으므로 살아있다는 것을 false 시킨다.
				m_bAlive = false;
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime();
			}
		}
		int a = 0;

	}
	break;

	case ENEMY_DEATHWAIT:
	{
		//이 행동에 대한 메시지를 방금 받았으면
		if (!m_bIsAction)
		{
			m_pBody->SetAnimationIndex(ENEMY_DEATHWAIT);
			m_bIsAction = true;
			m_fPeriod = 3.f;
		}

		if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				m_sState = ENEMY_DEATHWAIT;
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime();
			}
		}
		int a = 0;

	}
		break;
	
	case ENEMY_BACKPOSITION:
	{
		//만약 몬스터가 지정 범위에서 벗어났다면 자신의 오리진 위치로 돌아감
		float Length = D3DXVec3Length(&(m_vPosition - m_vOrigin));

		if (!m_bIsAction)
		{
			//달리기 모션으로 바꾸어 준다.
			m_bIsAction = true;
			m_pBody->SetAnimationIndex(ENEMY_RUN);
		}

		if (m_bIsAction)
		{
			if (abs(Length) < 1.f)
			{
				//생성 위치에 도달했다면? 다시 IDLE 상태로 돌린다.
				m_bIsAction = false;
				m_sState = ENEMY_IDLE;
			}

			//아직 생성 위치에 돌아오지 않았다면 계속 이동할 것
			else if (abs(Length) >= 1.f)
			{
				D3DXMATRIX matR;

				m_vDirection = m_vOrigin - m_vPosition;
				D3DXVec3Normalize(&m_vDirection, &m_vDirection);

				D3DXMatrixLookAtLH(&matR,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(m_vDirection.x, m_vDirection.y, m_vDirection.z),
					&D3DXVECTOR3(0, 1, 0));

				m_matWorld = matR * Move();
			}
		}

		int a = 0;

	}
		break;

	case ENEMY_RUN:
	{
		//동작 시간
		m_fPeriod = 1.f;

		//행동이 시작됨을 알림
		if (!m_bIsAction)
		{
			//Run 애니메이션 동작
			m_pBody->SetAnimationIndex(ENEMY_RUN);
			m_bIsAction = true;
			m_fAngle = RotateAngle();
		}

		if (m_bIsAction)
		{
			//주기 시간보다 지나간 시간이 크다면 IDLE 모션으로 전환
			if (m_fPassTime > m_fPeriod)
			{
				m_fPeriod = 0.f;
				m_fPassTime = 0.f;
				m_sState = ENEMY_IDLE;
				m_bIsAction = false;
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime();
				m_matWorld = Rotate() * Move();
			}
		}

		int a = 0;

	}
	break;
	case ENEMY_ATTACK:
		break;
	case ENEMY_SKILL1:
		break;
	case ENEMY_SKILL2:
		break;
	case ENEMY_CHASE:
	{
		//만약 몬스터가 지정 범위를 벗어나지 않았다면 플레이어를 쫒아간다.
		float Distance = D3DXVec3Length(&(m_vPosition - g_player->GetPosition()));

		if (!m_bIsAction)
		{
			m_bIsAction = true;
			m_pBody->SetAnimationIndex(ENEMY_RUN);
		}

		if (m_bIsAction)
		{
			if (abs(Distance) < 10.f)
			{
				//생성 위치에 도달했다면? 다시 IDLE 상태로 돌린다.
				m_bIsAction = false;
				m_sState = ENEMY_ATTACK;
			}

			//아직 생성 위치에 돌아오지 않았다면 계속 이동할 것
			else if (abs(Distance) >= 10.f)
			{
				D3DXMATRIX matR, matTemp;

				m_vDirection = g_player->GetPosition() - m_vPosition;
				D3DXVec3Normalize(&m_vDirection, &m_vDirection);

				D3DXMatrixLookAtLH(&matR,
					&D3DXVECTOR3(0, 0, 0),
					&-D3DXVECTOR3(m_vDirection.x, m_vDirection.y, m_vDirection.z),
					&D3DXVECTOR3(0, 1, 0));


				D3DXMatrixTranspose(&matR, &matR);
				/*D3DXMatrixRotationY(&matTemp, -D3DX_PI / 2.f);

				matR *= matTemp;*/

				m_matWorld = matR * Move();
			}

			//너무 벌어졌다면?
			else if (abs(Distance) >= 100.f)
			{
				D3DXMATRIX matR, matTemp;
				m_bIsAction = false;
				m_sState = ENEMY_BACKPOSITION;
			}
		}
		int a = 0;
	}
		break;
	}
}

D3DXMATRIXA16 cEnemy::Move()
{
	D3DXMATRIXA16 matT;

	m_vPosition = m_vPosition + m_vDirection * m_fSpeed;

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	
	return matT;
}

D3DXMATRIXA16 cEnemy::Rotate()
{
	D3DXMATRIXA16 matR;

	m_vDirection = D3DXVECTOR3(1, 0, 0);
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	
	return matR;
}

float cEnemy::RotateAngle()
{
	//순찰 시 몬스터가 바라보는 방향은 항상 다르다.
	float Angle = cRandomUtil::GetFloat(D3DX_PI * 2, 0);

	return Angle;
}