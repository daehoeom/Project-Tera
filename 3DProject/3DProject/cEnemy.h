#pragma once

#include "cCollisionObject.h"
#include "cBoundingSphere.h"

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
	virtual void OnCollisionStay(cCollisionObject* rhs) override;

	//몬스터 움직이기
	virtual D3DXMATRIXA16 Move();
	virtual D3DXMATRIXA16 Rotate();
	virtual float RotateAngle();

protected:
	cEnemySkinMesh*		m_pBody;		//몬스터 바디

	D3DXMATRIXA16		m_matWorld;	//몬스터의 월드매트릭스
	D3DXMATRIXA16		m_matLocal;
	D3DXMATRIXA16		matT;

	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vOrigin;	//몬스터가 생성된 초기 위치

	float				m_fSpeed;
	float				m_fAngle;
	float				m_fPeriod;
	float				m_fPassTime;
	float				m_fDeathTime;	//죽는 시간은 몬스터마다 달라서 설정해줌
	bool				m_bIsAction;

	int					n;
};

