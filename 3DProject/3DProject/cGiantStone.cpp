#include "stdafx.h"
#include "cGiantStone.h"
#include "cBody.h"

cGiantStone::cGiantStone()
{
	D3DXMatrixIdentity(&m_matWorld);

	m_pBody = new cBody;
	m_pBody->Setup("./CH/GiantStone", "GiantStone.X");

}


cGiantStone::~cGiantStone()
{
	SAFE_DELETE(m_pBody);
}

void cGiantStone::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}
}

void cGiantStone::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}