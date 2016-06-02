#include "stdafx.h"
#include "cGiantStone.h"
#include "cBody.h"

cGiantStone::cGiantStone()
{
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
		m_pBody->SetWorld(&this->GetWorld( ));
	}
}

void cGiantStone::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}