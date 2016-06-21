#include "stdafx.h"
#include "cPixie.h"

cPixie::cPixie()
{
	m_sName = "Pixie";

	m_pBody = new cNpcSkinnedMesh("./CH/Pixie/", "Pixie.X");

	D3DXMatrixRotationY(&m_matLocal, D3DX_PI / 2.f);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 30, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 15.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);
}


cPixie::~cPixie()
{
	SAFE_DELETE(m_pBody);
}

void cPixie::Update()
{
	__super::Update();

	if (GetEnemyState() == ENEMY_DEATH)
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y - 0.2f, GetPosition().z));
		m_fDeathTime = m_pBody->GetAniTrackPeriod(ENEMY_DEATH) - 0.5f;
		//이동량만큼 월드매트릭스 수정
		D3DXMatrixTranslation(&m_matWorld, GetPosition().x, GetPosition().y, GetPosition().z);
	}
}

void cPixie::Render()
{
	__super::Render();
}