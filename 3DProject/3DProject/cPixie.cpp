#include "stdafx.h"
#include "cPixie.h"
#include "cBody.h"

cPixie::cPixie()
{
	D3DXMatrixIdentity(&m_matWorld);

	m_pBody = new cBody;
	m_pBody->Setup("./CH/Pixie", "Pixie.X");

}


cPixie::~cPixie()
{
	SAFE_DELETE(m_pBody);
}

void cPixie::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}
}

void cPixie::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}