#include "stdafx.h"
#include "cMadmadDuo.h"
#include "cEnemySkinMesh.h"

cMadmadDuo::cMadmadDuo()

{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/MadmadDuo", "MadmanDuo.X");

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 15, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 15.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);

	D3DXMatrixTranslation(&matT, 0, 40, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 18.f));
	this->GetColliderRepo()[1]->SetLocal(&matT);

}


cMadmadDuo::~cMadmadDuo()
{
	SAFE_DELETE(m_pBody);
}

void cMadmadDuo::Update()
{
	__super::Update();

	for (auto& elem : this->GetColliderRepo())
	{
		elem->SetWorld(&m_matWorld);
	}
}

void cMadmadDuo::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}