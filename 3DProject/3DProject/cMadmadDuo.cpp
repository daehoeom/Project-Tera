#include "stdafx.h"
#include "cMadmadDuo.h"

cMadmadDuo::cMadmadDuo()
{
	m_sName = "Madmad";

	SetPosition(D3DXVECTOR3(-30, 0, 30));

	m_pBody = new cNpcSkinnedMesh("./CH/MadmadDuo/", "MadmanDuo.X");

	m_pBody->SetSpecTex(g_pTextureManager->GetTexture("./CH/MadmadDuo/MadmanDuo01_spec.tga"));

	D3DXMatrixRotationY(&m_matLocal, D3DX_PI / 2.f);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 15, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 30.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);
}


cMadmadDuo::~cMadmadDuo()
{
	SAFE_DELETE(m_pBody);
}

void cMadmadDuo::Update()
{
	__super::Update();

	if (GetEnemyState() == ENEMY_DEATH)
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y - 0.1f, GetPosition().z));
		m_fDeathTime = m_pBody->GetAniTrackPeriod(ENEMY_DEATH) - 0.4f;
		//이동량만큼 월드매트릭스 수정
		D3DXMatrixTranslation(&m_matWorld, GetPosition().x, GetPosition().y, GetPosition().z);
	}
}

void cMadmadDuo::Render()
{
	__super::Render();

}