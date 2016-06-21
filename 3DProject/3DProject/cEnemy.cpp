#include "stdafx.h"
#include "cEnemy.h"
#include "Console.h"

cEnemy::cEnemy()
	: n(0)
	, m_fSpeed(0.5f)
	, m_fAngle(0.f)
	, m_bIsAction(false)
	, m_bOncePlay(false)
	, m_vOrigin(0, 0, 0)
	, m_vDirection(1, 0, 0)
{
	this->SetCurrHp(50);
	SetEnemyState(ENEMY_IDLE);
	D3DXMatrixTranslation(&m_matWorld, GetPosition().x, GetPosition().y, GetPosition().z);

	m_vOrigin = this->GetPosition();

	this->SetObjectType(ObjectType::eMonster);

	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&matT);
}

cEnemy::~cEnemy()
{
	SAFE_DELETE( m_pBody );
}

void cEnemy::Update()
{
	__super::Update();

	//몬스터가 움직일 수 있는 일정 범위
	float Length = D3DXVec3Length(&(GetPosition() - m_vOrigin));
	//몬스터와 플레이어의 사이 거리 
	float Distance = D3DXVec3Length(&(GetPosition() - g_player->GetPosition()));

	m_fAttackCurrDelay += g_pTimeManager->GetDeltaTime();
	if (m_fAttackCurrDelay >= m_fAttackMaxTime)
	{
		m_fAttackCurrDelay = m_fAttackMaxTime;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		this->SetCurrHp(50);
		SetEnemyState(ENEMY_IDLE);
		this->SetDead(false);
		m_bIsAction = true;
		m_fPassTime = 0.f;
		m_fPeriod = 0.f;
	}

	//몬스터의 HP가 0인데 아직 죽음 처리가 안되었다면
	if (GetCurrHp() < 0.f && !this->IsDead())
	{
		//해당 이벤트가 실행 중이 아님
		if (GetEnemyState() != ENEMY_DEATH)
		{
			//실행 중인 행동을 중지하고 현재상태의 행동을 할 것
			m_bIsAction = false;

			//모든 죽음 처리가 다 끝났으므로 살아있다는 것을 false 시킨다.
			this->SetDead(true);
			SetEnemyState(ENEMY_DEATH);
		}
	}

	//만약 몬스터의 위치가 플레이어와 가깝다면 공격모션
	else if (abs(Distance) < 40.f && !this->IsDead() && GetEnemyState() != ENEMY_BACKPOSITION)
	{
		//해당 이벤트가 실행 중이 아님
		if (GetEnemyState() != ENEMY_ATTACK)
		{
			SetEnemyState(ENEMY_ATTACK);

			//실행 중인 행동을 중지하고 현재상태의 행동을 할 것
			m_bIsAction = false;
		}
	}

	//몬스터가 일정 범위를 넘어가면 다시 되돌아 올 것
	else if (abs(Length) > 300.f && !this->IsDead())
	{
		//해당 이벤트가 실행 중이 아님
		if (GetEnemyState() != ENEMY_BACKPOSITION && GetEnemyState() != ENEMY_CHASE &&
			GetEnemyState() != ENEMY_ATTACK)
		{
			SetEnemyState(ENEMY_BACKPOSITION);

			//실행 중인 행동을 중지하고 현재상태의 행동을 할 것
			m_bIsAction = false;
		}
	}

	//만약 몬스터의 상태가 되돌아가기가 아니라면 플레이어 쫒기
	else if (abs(Distance) < 100.f && !this->IsDead() && GetEnemyState() != ENEMY_BACKPOSITION)
	{
		//해당 이벤트가 실행 중이 아님
		if (GetEnemyState() != ENEMY_CHASE && GetEnemyState() != ENEMY_ATTACK)
		{
			SetEnemyState(ENEMY_CHASE);

			//실행 중인 행동을 중지하고 현재상태의 행동을 할 것
			m_bIsAction = false;
		}
	}

	ActionState();
	
	for (size_t i = 0; i < this->GetColliderRepo().size(); i++)
	{
		this->GetColliderRepo()[i]->SetWorld(&m_matWorld);
		D3DXMATRIXA16 mat = this->GetColliderRepo()[i]->GetLocal() * this->GetColliderRepo()[i]->GetWorld();
		D3DXVECTOR3 vPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
		this->GetColliderRepo()[i]->SetPosition(vPos);
	}

	m_pBody->SetWorld(&m_matWorld);
}

void cEnemy::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->UpdateAndRender();
	}
}

void cEnemy::ActionState()
{
	switch (GetEnemyState())
	{
	case ENEMY_IDLE:
	{
		//이 행동에 대한 메시지를 방금 받았으면
		if (!m_bIsAction)
		{
			m_pBody->SetAnimationIndex(ENEMY_IDLE);
			m_bIsAction = true;
			m_fPeriod = m_pBody->GetAniTrackPeriod(ENEMY_IDLE);
		}

		//모든 대기시간이 종료되면 순찰하기로 돌아간다.
		if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_fPeriod = 0.f;
				m_fPassTime = 0.f;
				SetEnemyState(ENEMY_RUN);
				m_bIsAction = false;
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime();
			}
		}
	}
	break;

	case ENEMY_DEATH:
	{
		//이 행동에 대한 메시지를 방금 받았으면
		if (!m_bIsAction)
		{
			std::string Name;
			Name = m_sName + std::string("죽음");
			SOUNDMANAGER->play(Name, 1.f);
			m_bIsAction = true;
			m_pBody->SetAnimationIndex(ENEMY_DEATH);
			m_fPassTime = 0.f;
		}

		if (m_bIsAction)
		{
			if (m_fPassTime > m_fDeathTime)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetEnemyState(ENEMY_DEATHWAIT);
			}

			else if (m_fPassTime < m_fDeathTime)
			{
				Log(m_fPassTime);
				Log("\n");
				m_fPassTime += g_pTimeManager->GetDeltaTime();
			}
		}
	}
	break;

	case ENEMY_DEATHWAIT:
	{
		//이 행동에 대한 메시지를 방금 받았으면
		if (!m_bIsAction)
		{
			m_pBody->SetAnimationIndex(ENEMY_DEATHWAIT);
			m_bIsAction = true;
			m_fPeriod = m_pBody->GetAniTrackPeriod(ENEMY_DEATHWAIT);
		}

		if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetEnemyState(ENEMY_NOTHING);
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime();
			}
		}
	}
	break;

	case ENEMY_BACKPOSITION:
	{
		//만약 몬스터가 지정 범위에서 벗어났다면 자신의 오리진 위치로 돌아감
		float Length = D3DXVec3Length(&(GetPosition() - m_vOrigin));

		if (!m_bIsAction)
		{
			//달리기 모션으로 바꾸어 준다.
			m_bIsAction = true;
			m_pBody->SetAnimationIndex(ENEMY_RUN);
			int a = 0;
		}

		if (m_bIsAction)
		{
			if (abs(Length) < 40.f)
			{
				//생성 위치에 도달했다면? 다시 IDLE 상태로 돌린다.
				m_bIsAction = false;
				SetEnemyState(ENEMY_IDLE);
			}

			//아직 생성 위치에 돌아오지 않았다면 계속 이동할 것
			else if (abs(Length) >= 40.f)
			{
				D3DXMATRIX matR;

				m_vDirection = m_vOrigin - GetPosition();
				D3DXVec3Normalize(&m_vDirection, &m_vDirection);

				D3DXMatrixLookAtLH(&matR,
					&D3DXVECTOR3(0, 0, 0),
					&-D3DXVECTOR3(m_vDirection.x, m_vDirection.y, m_vDirection.z),
					&D3DXVECTOR3(0, 1, 0));

				D3DXMatrixTranspose(&matR, &matR);

				m_matWorld = matR * Move();
				m_matWorld = m_matLocal * m_matWorld;
			}
		}
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
				SetEnemyState(ENEMY_IDLE);
				m_bIsAction = false;
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime() ;
				m_matWorld = Rotate() * Move();
			}
		}
	}
	break;
	case ENEMY_ATTACK:
	{
		//만약 몬스터가 지정 범위를 벗어나지 않았다면 플레이어를 쫒아간다.
		float Distance = D3DXVec3Length(&(GetPosition() - g_player->GetPosition()));
		
		if (!m_bIsAction)
		{
			std::string Name;
			Name = m_sName + std::string("공격");
			SOUNDMANAGER->play(Name, 1.f);

			m_bIsAction = true;
			m_pBody->SetAnimationIndex(ENEMY_ATTACK);
			m_fPeriod = m_pBody->GetAniTrackPeriod(ENEMY_ATTACK);
		}

		else if (m_bIsAction)
		{
			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;

				if (abs(Distance) < 20.f)
				{
					SetEnemyState(ENEMY_ATTACK);
				}

				else if (abs(Distance) > 50.f)
				{
					SetEnemyState(ENEMY_CHASE);
				}
			}

			else if (m_fPassTime < m_fPeriod)
			{
				m_fPassTime += g_pTimeManager->GetDeltaTime();
			}
		}
	}
		break;
	case ENEMY_SKILL1:
		break;
	case ENEMY_SKILL2:
		break;
	case ENEMY_CHASE:
	{
		//만약 몬스터가 지정 범위를 벗어나지 않았다면 플레이어를 쫒아간다.
		float Distance = D3DXVec3Length(&(GetPosition() - g_player->GetPosition()));

		if (!m_bIsAction)
		{
			m_bIsAction = true;
			m_pBody->SetAnimationIndex(ENEMY_RUN);
			int a = 0;
		}

		if (m_bIsAction)
		{
			float Length = D3DXVec3Length(&(GetPosition() - m_vOrigin));
			
			//플레이어와 멀어졌다면 계속 따라갈 것
			D3DXMATRIX matR, matTemp;

			m_vDirection = g_player->GetPosition() - GetPosition();
			D3DXVec3Normalize(&m_vDirection, &m_vDirection);

			D3DXMatrixLookAtLH(&matR,
				&D3DXVECTOR3(0, 0, 0),
				&-D3DXVECTOR3(m_vDirection.x, m_vDirection.y, m_vDirection.z),
				&D3DXVECTOR3(0, 1, 0));


			D3DXMatrixTranspose(&matR, &matR);
			/*D3DXMatrixRotationY(&matTemp, -D3DX_PI / 2.f);

			matR *= matTemp;*/

			m_matWorld = matR * Move();
			m_matWorld = m_matLocal * m_matWorld;
			
			//일정 범위를 넘어섰거나, 플레이어와 충분히 거리가 벌려졌다면
			if (abs(Length) > 600.f || abs(Distance) > 300.f)
			{
				SetEnemyState(ENEMY_BACKPOSITION);
			}
		}
	}
	break;
	}
}

D3DXMATRIXA16 cEnemy::Move()
{
	D3DXMATRIXA16 matT;

	SetPosition(GetPosition() + m_vDirection * m_fSpeed);

	D3DXMatrixTranslation(&matT, GetPosition().x, GetPosition().y, GetPosition().z);

	return matT;
}

void cEnemy::OnCollisionStay(cCollisionObject* rhs)
{
	//if (rhs->GetCollisionType() == CollisionType::ePlayer && !this->GetCollision())
	//{
	//	if (GetEnemyState() == ENEMY_ATTACK)
	//	{
	//		Log("충돌하였음");
	//		this->SetCollision(true);
	//		rhs->SetCurrHp(rhs->GetCurrHp() - 100);
	//		int a = 0;
	//	}
	//}
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

