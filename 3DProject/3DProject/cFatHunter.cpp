#include "stdafx.h"
#include "cFatHunter.h"
#include "cEnemySkinMesh.h"

cFatHunter::cFatHunter()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/FatHunter", "FatHunter.X");

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 50, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 30.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);

	D3DXMatrixTranslation(&matT, 0, 30, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 30.f));
	this->GetColliderRepo()[1]->SetLocal(&matT);
}


cFatHunter::~cFatHunter()
{
	SAFE_DELETE(m_pBody);
}

void cFatHunter::Update()
{
	__super::Update();

	for (auto& elem : this->GetColliderRepo())
	{
		elem->SetWorld(&m_matWorld);
	}
}

void cFatHunter::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}