#include "stdafx.h"
#include "cMadmadDuo.h"
#include "cBody.h"

cMadmadDuo::cMadmadDuo()

{
	D3DXMatrixIdentity(&m_matWorld);

	m_pBody = new cBody;
	m_pBody->Setup("./CH/MadmadDuo", "MadmanDuo.X");

}


cMadmadDuo::~cMadmadDuo()
{
	SAFE_DELETE(m_pBody);
}

void cMadmadDuo::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}
}

void cMadmadDuo::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}