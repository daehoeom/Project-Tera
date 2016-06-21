#include "stdafx.h"
#include "cGiantStone.h"

cGiantStone::cGiantStone()
{
	m_sName = "GiantStone";

	m_pBody = new cNpcSkinnedMesh("./CH/GiantStone/", "GiantStone.X");

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 50, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 50.f));
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
}