#include "stdafx.h"
#include "cEnemy.h"
#include "Console.h"
#include "cParticle_Death.h"
#include "cHPGaugeBar.h"

cEnemy::cEnemy()
	: n(0)
	, m_fSpeed(0.5f)
	, m_fAngle(0.f)
	, m_bIsAction(false)
	, m_vOrigin(0, 0, 0)
	, m_vDirection(1, 0, 0)
	, m_pParticle(nullptr)
	, m_pBody(nullptr)
	, m_CollisionTime(0.f)
	, m_enemyHPBar(new cHPGaugeBar("CH/UIImage/HPBar_0.png", "CH/UIImage/HPBar_1.png"))
{
	for (size_t i = 0; i < _countof(m_aPlane); i++)
	{
		m_aPlane[i] = D3DXPLANE(0, 0, 0, 0);
	}

	//this->SetCurrHp(50);
	SetEnemyState(ENEMY_IDLE);
	D3DXMatrixTranslation(&m_matWorld, GetPosition().x, GetPosition().y, GetPosition().z);

	m_vOrigin = this->GetPosition();

	this->SetObjectType(ObjectType::eMonster);

	m_pParticle = new cParticle_Death;
	m_pParticle->Setup("./CH/Shadow/Noise.tga");

	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&matT);

	m_enemyHPBar->SetOwner( this );
	m_enemyHPBar->SetScale( { 103.f/6, 15.f/6, 1.f } );
	m_enemyHPBar->Move( { 0.f, 70.f, 0.f } );

}

cEnemy::~cEnemy()
{
	SAFE_DELETE(m_pParticle);
	SAFE_DELETE( m_pBody );
	SAFE_DELETE( m_enemyHPBar );
}

void cEnemy::Update()
{
	__super::Update();

	m_enemyHPBar->Update();

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
	else if (abs(Distance) - 11.f < m_fRange && !this->IsDead() && GetEnemyState() != ENEMY_BACKPOSITION)
	{
		//해당 이벤트가 실행 중이 아님
		if (GetEnemyState() != ENEMY_ATTACK)
		{
			SetEnemyState(ENEMY_ATTACK);

			g_player->SetCurrHp( g_player->GetCurrHp( ) - 30 );
			Log( "몬스터 ", this->GetName( ).c_str( ), "가 플레이어[HP:", g_player->GetCurrHp( ),"]를 공격 on ENEMY_CHASE\n" );

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

	if (this->GetCollision() && !this->IsDead())
	{
		m_CollisionTime += g_pTimeManager->GetDeltaTime();

		m_pBody->SetDiffColor(3.f);

		if (m_CollisionTime > 0.4f)
		{
			m_pBody->SetDiffColor(1.f);
			this->SetCollision(false);
			m_CollisionTime = 0.f;
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

	D3DXMATRIX matProj, matView;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	ConstructFrustum(1000.f, matProj, matView);
}

void cEnemy::Render()
{
	__super::Render();

	if ( m_enemyHPBar )
	{
		m_enemyHPBar->Render( );
	}

	if (CheckSphere(this->GetPosition().x, this->GetPosition().y, this->GetPosition().z, 5.f))
	{
		if (m_pBody)
		{
			m_pBody->UpdateAndRender();
		}
	}

	if (this->GetEnemyState() == ENEMY_DEATHWAIT && m_bIsAction)
	{
		if (!m_pParticle->IsDead())
		{
			m_pParticle->Render();
		}
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
			m_pParticle->SetParticle(this->GetPosition());
			m_pBody->SetAnimationIndex(ENEMY_DEATHWAIT);
			m_bIsAction = true;
			m_fPeriod = m_pBody->GetAniTrackPeriod(ENEMY_DEATHWAIT) + 10.f;
		}

		if (m_bIsAction)
		{
			m_pParticle->Update();

			if (m_fPassTime > m_fPeriod)
			{
				m_bIsAction = false;
				m_fPassTime = 0.f;
				m_fPeriod = 0.f;
				SetEnemyState(ENEMY_NOTHING);
				this->SetActive(false);
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
			if (abs(Length) < 100.f)
			{
				//생성 위치에 도달했다면? 다시 IDLE 상태로 돌린다.
				m_bIsAction = false;
				SetEnemyState(ENEMY_IDLE);
			}

			//아직 생성 위치에 돌아오지 않았다면 계속 이동할 것
			else if (abs(Length) >= 100.f)
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

				g_player->SetCurrHp( g_player->GetCurrHp( )-30 );
				Log( "몬스터 ", this->GetName( ).c_str( ), "가 플레이어[HP:", g_player->GetCurrHp( ), "]를 공격 on ENEMY_CHASE\n" );

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

void cEnemy::ConstructFrustum(float screenDepth, D3DXMATRIX proj, D3DXMATRIX view)
{
	D3DXVECTOR3 v[8];

	v[0] = D3DXVECTOR3(-1, -1, 0);
	v[1] = D3DXVECTOR3(1, -1, 0);
	v[2] = D3DXVECTOR3(-1, 1, 0);
	v[3] = D3DXVECTOR3(1, 1, 0);
	v[4] = D3DXVECTOR3(-1, -1, 1);
	v[5] = D3DXVECTOR3(1, -1, 1);
	v[6] = D3DXVECTOR3(-1, 1, 1);
	v[7] = D3DXVECTOR3(1, 1, 1);

	D3DXMATRIX matInv;

	matInv = view * proj;
	D3DXMatrixInverse(&matInv, NULL, &matInv);

	D3DXVec3TransformCoord(&v[0], &v[0], &matInv);
	D3DXVec3TransformCoord(&v[1], &v[1], &matInv);
	D3DXVec3TransformCoord(&v[2], &v[2], &matInv);
	D3DXVec3TransformCoord(&v[3], &v[3], &matInv);
	D3DXVec3TransformCoord(&v[4], &v[4], &matInv);
	D3DXVec3TransformCoord(&v[5], &v[5], &matInv);
	D3DXVec3TransformCoord(&v[6], &v[6], &matInv);
	D3DXVec3TransformCoord(&v[7], &v[7], &matInv);

	//근평면
	D3DXPlaneFromPoints(&m_aPlane[0], &v[1], &v[0], &v[2]);

	//우평면
	D3DXPlaneFromPoints(&m_aPlane[1], &v[5], &v[1], &v[3]);

	//상평면
	D3DXPlaneFromPoints(&m_aPlane[2], &v[3], &v[2], &v[6]);

	//원평면
	D3DXPlaneFromPoints(&m_aPlane[3], &v[4], &v[5], &v[7]);

	//좌평면
	D3DXPlaneFromPoints(&m_aPlane[4], &v[0], &v[4], &v[2]);

	//하평면
	D3DXPlaneFromPoints(&m_aPlane[5], &v[0], &v[1], &v[5]);
}

bool cEnemy::CheckSphere(float x, float y, float z, float radius)
{
	for (int i = 0; i < 6; i++)
	{
		if (D3DXPlaneDotCoord(&m_aPlane[i], &D3DXVECTOR3(x, y, z)) > radius)
		{
			return false;
		}
	}
	return true;
}