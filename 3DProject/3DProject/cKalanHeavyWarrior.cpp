#include "stdafx.h"
#include "cKalanHeavyWarrior.h"
#include "cEnemySkinMesh.h"

cKalanHeavyWarrior::cKalanHeavyWarrior()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/KalanHeavyWarrior", "KalanHeavyWarrior.X");

	SetPosition(D3DXVECTOR3(0.f, -2.f, 0.f));
	Move();

	D3DXMatrixTranslation(&m_matLocal, 0, -15, 0);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 40, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 40.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);
}


cKalanHeavyWarrior::~cKalanHeavyWarrior()
{
	SAFE_DELETE(m_pBody);
}

void cKalanHeavyWarrior::Update()
{
	__super::Update();

	if (GetEnemyState() == ENEMY_DEATH)
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, GetPosition().z));
		m_fDeathTime = m_pBody->GetAniTrackPeriod(ENEMY_DEATH) - 2.5f;
		//이동량만큼 월드매트릭스 수정
		D3DXMatrixTranslation(&m_matWorld, GetPosition().x, GetPosition().y, GetPosition().z);
	}
}

void cKalanHeavyWarrior::Render()
{
	__super::Render();
}