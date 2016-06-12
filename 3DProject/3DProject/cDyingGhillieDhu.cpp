#include "stdafx.h"
#include "cDyingGhillieDhu.h"
#include "cEnemySkinMesh.h"

cDyingGhillieDhu::cDyingGhillieDhu()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/DyingGhillieDhu", "DyingGhillieDhu.X");

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 50, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 30.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);

	D3DXMatrixTranslation(&matT, 0, 30, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 30.f));
	this->GetColliderRepo()[1]->SetLocal(&matT);
}


cDyingGhillieDhu::~cDyingGhillieDhu()
{
	SAFE_DELETE(m_pBody);
}

void cDyingGhillieDhu::Update()
{
	__super::Update();

	for (auto& elem : this->GetColliderRepo())
	{
		elem->SetWorld(&m_matWorld);
	}
}

void cDyingGhillieDhu::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}