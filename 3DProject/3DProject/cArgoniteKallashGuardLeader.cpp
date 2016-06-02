#include "stdafx.h"
#include "cArgoniteKallashGuardLeader.h"
#include "cBody.h"

cArgoniteKallashGuardLeader::cArgoniteKallashGuardLeader()
{
	D3DXMatrixIdentity(&m_matWorld);

	m_pBody = new cBody;
	m_pBody->Setup("./CH/ArgoniteKallashGuardLeader", "ArgoniteKallashGuardLeader.X");

}


cArgoniteKallashGuardLeader::~cArgoniteKallashGuardLeader()
{
	SAFE_DELETE(m_pBody);
}

void cArgoniteKallashGuardLeader::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}
}

void cArgoniteKallashGuardLeader::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}