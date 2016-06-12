#include "stdafx.h"
#include "cKalanHeavyWarrior.h"
#include "cEnemySkinMesh.h"

cKalanHeavyWarrior::cKalanHeavyWarrior()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/KalanHeavyWarrior", "KalanHeavyWarrior.X");

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

	for (auto& elem : this->GetColliderRepo())
	{
		elem->SetWorld(&m_matWorld);
	}
}

void cKalanHeavyWarrior::Render()
{
	__super::Render();
}