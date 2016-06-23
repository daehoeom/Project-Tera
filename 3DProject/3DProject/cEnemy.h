#pragma once
#include "cUnitObject.h"
#include "cBoundingSphere.h"

class cNpcSkinnedMesh;
class cParticle_Death;

enum eEnemyState
{
	ENEMY_IDLE = 0,				//몬스터 서있기
	ENEMY_RUN = 1,				//몬스터 이동
	ENEMY_DEATHWAIT = 2,		//몬스터 죽음
	ENEMY_DEATH = 3,			//몬스터 죽기 직전
	ENEMY_ATTACK = 4,			//몬스터 공격
	ENEMY_SKILL1 = 5,			//몬스터 스킬1
	ENEMY_SKILL2 = 6,			//몬스터 스킬2
	ENEMY_BACKPOSITION = 7,		//몬스터 되돌아가기
	ENEMY_CHASE = 8,			//플레이어 쫒아가기
	ENEMY_NOTHING
};

class cEnemy :
	public cUnitObject
{
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Update() override;
	virtual void Render() override;
	virtual void ActionState();
	virtual void OnCollisionStay(cCollisionObject* rhs) override ;

	//몬스터 움직이기
	virtual D3DXMATRIXA16 Move();
	virtual D3DXMATRIXA16 Rotate();
	virtual float RotateAngle();

	void SetEnemyState( eEnemyState e );
	eEnemyState GetEnemyState( );
	void SetEnemyOrigin(D3DXVECTOR3* v);
	D3DXVECTOR3 GetEnemyOrigin();
	void ResetAttackDelay( );
	bool IsAbleAttacked( );

	void ConstructFrustum(float screenDepth, D3DXMATRIX proj, D3DXMATRIX view);
	bool CheckSphere(float x, float y, float z, float radius);

protected:
	eEnemyState m_sEState;

	cNpcSkinnedMesh*	m_pBody;
	cParticle_Death*	m_pParticle;

	D3DXMATRIXA16		m_matWorld;	//몬스터의 월드매트릭스
	D3DXMATRIXA16		m_matLocal;
	D3DXMATRIXA16		matT;
	D3DXPLANE			m_aPlane[6];

	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vOrigin;	//몬스터가 생성된 초기 위치

	std::string			m_sName;

	float				m_fSpeed;
	float				m_fAngle;
	float				m_fPeriod;
	float				m_fPassTime;
	float				m_CollisionTime;
	float				m_fRange;
	float				m_fDeathTime;	//죽는 시간은 몬스터마다 달라서 설정해줌
	bool				m_bIsAction;

	int					n;
	float				m_fAttackCurrDelay;
	float				m_fAttackMaxTime;

	std::vector<cEnemy*> m_vecEnemy;
};

inline void cEnemy::ResetAttackDelay( )
{
	m_fAttackCurrDelay = 0.f;
}

inline bool cEnemy::IsAbleAttacked( )
{
	return ( m_fAttackMaxTime - m_fAttackCurrDelay ) <= 0.001f;
}

inline void cEnemy::SetEnemyState( eEnemyState e )
{
	m_sEState = e;
}

inline eEnemyState cEnemy::GetEnemyState( )
{
	return m_sEState;
}

inline void cEnemy::SetEnemyOrigin(D3DXVECTOR3* v)
{
	m_vOrigin = *v;
}

inline D3DXVECTOR3 cEnemy::GetEnemyOrigin()
{
	return m_vOrigin;
}