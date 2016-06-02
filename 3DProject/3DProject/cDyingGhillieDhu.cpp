#include "stdafx.h"
#include "cDyingGhillieDhu.h"
#include "cBody.h"

cDyingGhillieDhu::cDyingGhillieDhu()
{
	m_pBody = new cBody;
	m_pBody->Setup("./CH/DyingGhillieDhu", "DyingGhillieDhu.X");
}


cDyingGhillieDhu::~cDyingGhillieDhu()
{
	SAFE_DELETE(m_pBody);
}

void cDyingGhillieDhu::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&this->GetWorld( ));
	}
}

void cDyingGhillieDhu::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}