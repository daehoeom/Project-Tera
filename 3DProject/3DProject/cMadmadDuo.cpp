#include "stdafx.h"
#include "cMadmadDuo.h"

cMadmadDuo::cMadmadDuo()
{
	SetPosition(D3DXVECTOR3(-30, 0, 30));

	//m_pBody = new cEnemySkinMesh;
	//m_pBody->Setup("./CH/MadmadDuo", "MadmanDuo.X");

	/*D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, D3DX_PI / 2.f);
	m_pBody->SetLocal(&matR);*/

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 15, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 15.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);

	D3DXMatrixTranslation(&matT, 0, 40, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 18.f));
	this->GetColliderRepo()[1]->SetLocal(&matT);
}


cMadmadDuo::~cMadmadDuo()
{
}

void cMadmadDuo::Update()
{
	__super::Update();

	//if (GetEnemyState() == ENEMY_DEATH)
	//{
	//	SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y - 0.1f, GetPosition().z));
	//	m_fDeathTime = m_pBody->GetAniTrackPeriod(ENEMY_DEATH) - 1.7f;
	//	//이동량만큼 월드매트릭스 수정
	//	D3DXMatrixTranslation(&m_matWorld, GetPosition().x, GetPosition().y, GetPosition().z);
	//}
}

void cMadmadDuo::Render()
{
	__super::Render();

}