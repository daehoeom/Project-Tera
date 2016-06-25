#include "stdafx.h"
#include "cPlayerSkill.h"
#include "cUIObject.h"
#include "cUIImageView.h"

cPlayerSkill::cPlayerSkill()
	: m_pSkill(nullptr)
	, m_pSprite(nullptr)
{
	cUIImageView* pView = new cUIImageView;
	pView->SetViewTexture("./CH/UIImage/SkillSlot.png");
	pView->SetPosition({ 500, 550, 0 });
	m_pSkill = pView;

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}



cPlayerSkill::~cPlayerSkill()
{
	SAFE_RELEASE(m_pSprite);

	if (m_pSkill)
	{
		m_pSkill->Destroy();
		m_pSkill = nullptr;
	}
}

void cPlayerSkill::Update()
{
	if (m_pSkill)
	{
		m_pSkill->Update();
	}
}

void cPlayerSkill::Render()
{
	if (m_pSkill)
	{
		m_pSkill->Render(m_pSprite);
	}
}