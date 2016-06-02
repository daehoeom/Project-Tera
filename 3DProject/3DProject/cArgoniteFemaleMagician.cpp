#include "stdafx.h"
#include "cArgoniteFemaleMagician.h"
#include "cBody.h"

cArgoniteFemaleMagician::cArgoniteFemaleMagician()
{
	D3DXMatrixIdentity(&m_matWorld);

	m_pBody = new cBody;
	m_pBody->Setup("./CH/ArgoniteFemaleMagician", "ArgoniteFemaleMagician.X");

}


cArgoniteFemaleMagician::~cArgoniteFemaleMagician()
{
	SAFE_DELETE(m_pBody);
}

void cArgoniteFemaleMagician::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}
}

void cArgoniteFemaleMagician::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}