#include "stdafx.h"
#include "cArgoniteKallashGuardLeader.h"
#include "cEnemySkinMesh.h"

cArgoniteKallashGuardLeader::cArgoniteKallashGuardLeader()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/ArgoniteKallashGuardLeader", "ArgoniteKallashGuardLeader.X");

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 30.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);
}


cArgoniteKallashGuardLeader::~cArgoniteKallashGuardLeader()
{
	SAFE_DELETE(m_pBody);
}

void cArgoniteKallashGuardLeader::Update()
{
	__super::Update();

	for (auto& elem : this->GetColliderRepo())
	{
		elem->SetWorld(&m_matWorld);
	}
}

void cArgoniteKallashGuardLeader::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}