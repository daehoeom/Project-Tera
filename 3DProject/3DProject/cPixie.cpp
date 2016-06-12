#include "stdafx.h"
#include "cPixie.h"
#include "cEnemySkinMesh.h"

cPixie::cPixie()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/Pixie", "Pixie.X");

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

	for (auto& elem : this->GetColliderRepo())
	{
		elem->SetWorld(&m_matWorld);
	}
}

void cPixie::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}