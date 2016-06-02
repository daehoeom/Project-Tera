#include "stdafx.h"
#include "cKalanHeavyWarrior.h"
#include "cBody.h"

cKalanHeavyWarrior::cKalanHeavyWarrior()
{
	m_pBody = new cBody;
	m_pBody->Setup("./CH/KalanHeavyWarrior", "KalanHeavyWarrior.X");
}


cKalanHeavyWarrior::~cKalanHeavyWarrior()
{
	SAFE_DELETE(m_pBody);
}

void cKalanHeavyWarrior::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&this->GetWorld( ));
	}
}

void cKalanHeavyWarrior::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}
}