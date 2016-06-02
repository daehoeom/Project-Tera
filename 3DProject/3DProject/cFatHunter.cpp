#include "stdafx.h"
#include "cFatHunter.h"
#include "cBody.h"

cFatHunter::cFatHunter()
{
	D3DXMatrixIdentity(&m_matWorld);

	m_pBody = new cBody;
	m_pBody->Setup("./CH/FatHunter", "FatHunter.X");
}


cFatHunter::~cFatHunter()
{
	SAFE_DELETE(m_pBody);
}

void cFatHunter::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}
}

void cFatHunter::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}