#include "stdafx.h"
#include "cArgoniteKallashGuardLeader.h"

cArgoniteKallashGuardLeader::cArgoniteKallashGuardLeader()
{
	m_pBody = new cNpcSkinnedMesh("./CH/ArgoniteKallashGuardLeader/", "ArgoniteKallashGuardLeader.X");

	D3DXMatrixRotationY(&m_matLocal, D3DX_PI / 2.f);
	//m_pBody->SetLocal(&matR);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 30.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);
}


cArgoniteKallashGuardLeader::~cArgoniteKallashGuardLeader()
{
	SAFE_DELETE(m_pBody);
}

void cArgoniteKallashGuardLeader::Update()
{
	__super::Update();

	if (GetEnemyState() == ENEMY_DEATH)
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y - 0.1f, GetPosition().z));
		m_fDeathTime = m_pBody->GetAniTrackPeriod(ENEMY_DEATH) - 2.4f;
		//이동량만큼 월드매트릭스 수정
		D3DXMatrixTranslation(&m_matWorld, GetPosition().x, GetPosition().y, GetPosition().z);
	}
}

void cArgoniteKallashGuardLeader::Render()
{
	__super::Render();
	
}