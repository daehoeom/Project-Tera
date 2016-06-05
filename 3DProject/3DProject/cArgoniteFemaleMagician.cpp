#include "stdafx.h"
#include "cArgoniteFemaleMagician.h"
#include "cEnemySkinMesh.h"

cArgoniteFemaleMagician::cArgoniteFemaleMagician()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/ArgoniteFemaleMagician", "ArgoniteFemaleMagician.X");

	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, D3DX_PI / 2.f);
	m_pBody->SetLocal(&matR);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 50, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));
	this->GetColliderRepo()[0]->SetLocal(&matT);

	D3DXMatrixTranslation(&matT, 0, 30, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));
	this->GetColliderRepo()[1]->SetLocal(&matT);
}


cArgoniteFemaleMagician::~cArgoniteFemaleMagician()
{
	SAFE_DELETE(m_pBody);
}

void cArgoniteFemaleMagician::Update()
{
	__super::Update();

	for (size_t i = 0; i < this->GetColliderRepo().size(); i++)
	{
		this->GetColliderRepo()[i]->SetWorld(&m_matWorld);
	}
}

void cArgoniteFemaleMagician::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}