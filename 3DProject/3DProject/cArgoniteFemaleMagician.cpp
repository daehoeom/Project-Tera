#include "stdafx.h"
#include "cArgoniteFemaleMagician.h"
#include "cBody.h"

cArgoniteFemaleMagician::cArgoniteFemaleMagician()
{
	m_pBody = new cBody;
	m_pBody->Setup("./CH/ArgoniteFemaleMagician", "ArgoniteFemaleMagician.X");

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 10, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));
	this->GetCollider()->SetLocal(&matT);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));
}


cArgoniteFemaleMagician::~cArgoniteFemaleMagician()
{
	SAFE_DELETE(m_pBody);
}

void cArgoniteFemaleMagician::Update()
{
	__super::Update();

	this->GetCollider()->SetWorld(&m_matWorld);
	
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&this->GetWorld( ));
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