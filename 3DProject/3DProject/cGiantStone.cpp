#include "stdafx.h"
#include "cGiantStone.h"
#include "cEnemySkinMesh.h"

cGiantStone::cGiantStone()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/GiantStone", "GiantStone.X");

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 50, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 50.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);
}


cGiantStone::~cGiantStone()
{
	SAFE_DELETE(m_pBody);
}

void cGiantStone::Update()
{
	__super::Update();

	for (auto& elem : this->GetColliderRepo())
	{
		elem->SetWorld(&m_matWorld);
	}
}

void cGiantStone::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}