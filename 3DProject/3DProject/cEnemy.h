#pragma once

#include "cCollisionObject.h"
#include "cBoundingSphere.h"

enum eEnemyState
{
	ENEMY_IDLE			= 0,		//몬스터 서있기
	ENEMY_RUN			= 1,		//몬스터 이동
	ENEMY_DEATHWAIT		= 2,		//몬스터 죽음
	ENEMY_DEATH			= 3,		//몬스터 죽기 직전
	ENEMY_ATTACK		= 4,		//몬스터 공격
	ENEMY_SKILL1		= 5,		//몬스터 스킬1
	ENEMY_SKILL2		= 6,		//몬스터 스킬2
	ENEMY_BACKPOSITION	= 7,		//몬스터 되돌아가기
	ENEMY_CHASE			= 8,		//플레이어 쫒아가기
};

class cEnemySkinMesh;

class cEnemy :
	public cCollisionObject
{
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Update() override;
	virtual void Render() override;
	virtual void ActionState();

	virtual int GetCurrentHp() { return m_nCurrentHp; }
	virtual int GetMaxHp() { return m_nMaxHp; }
	virtual void SetCurrentHp(int currHp) { m_nCurrentHp = currHp; }

	//몬스터 움직이기
	virtual D3DXMATRIXA16 Move();
	virtual D3DXMATRIXA16 Rotate();
	virtual float RotateAngle();

	virtual void SetPosition(D3DXVECTOR3* vPos) { m_vPosition = *vPos; }
	virtual D3DXVECTOR3 GetPosition() { return m_vPosition; }

protected:
	cEnemySkinMesh*		m_pBody;		//몬스터 바디

	int	  				m_nMaxHp;		//몬스터의 최대 피
	int	  				m_nCurrentHp;	//현재몬스터의 피

	D3DXMATRIXA16		m_matWorld;	//몬스터의 월드매트릭스
	D3DXMATRIXA16		m_matLocal;
	D3DXMATRIXA16		matT;

	D3DXVECTOR3			m_vPosition;
	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vOrigin;	//몬스터가 생성된 초기 위치

	float				m_fSpeed;
	float				m_fAngle;
	float				m_fPeriod;
	float				m_fPassTime;

	bool				m_bIsAction;
	bool				m_bAlive;

	eEnemyState			m_sState;
	int				n;
};

