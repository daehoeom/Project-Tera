#include "stdafx.h"
#include "cPlayerGauge.h"
#include "cUIObject.h"
#include "cUIImageView.h"


cPlayerGauge::cPlayerGauge()
	: m_pHpFrame(nullptr)
	, m_pManaFrame(nullptr)
	, m_pSprite(nullptr)
	, m_fEnergyWidth(0)
	, m_fManaWidth(0)
{
	cUIImageView* pFrame = new cUIImageView;
	pFrame->SetViewTexture("./CH/UIImage/EnergyFrame.png");
	pFrame->SetPosition({ 220, 630, 0 });
	m_pHpFrame = pFrame;

	cUIImageView* Hp = new cUIImageView;
	Hp->SetViewTexture("./CH/UIImage/에너지바.png");
	Hp->SetPosition({ 53, 12, 0 });
	m_pHpFrame->AddChild(Hp);

	pFrame = new cUIImageView;
	pFrame->SetViewTexture("./CH/UIImage/EnergyFrame.png");
	pFrame->SetPosition({ 720, 630, 0 });
	m_pManaFrame = pFrame;

	cUIImageView* mana = new cUIImageView;
	mana->SetViewTexture("./CH/UIImage/마나게이지.png");
	mana->SetPosition({ 53, 12, 0 });
	m_pManaFrame->AddChild(mana);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}


cPlayerGauge::~cPlayerGauge()
{
	SAFE_RELEASE(m_pSprite);

	if (m_pHpFrame)
	{
		m_pHpFrame->Destroy();
		m_pHpFrame = nullptr;
	}

	if (m_pManaFrame)
	{
		m_pManaFrame->Destroy();
		m_pManaFrame = nullptr;
	}
}

void cPlayerGauge::Update()
{
	D3DXMATRIXA16 matHpWorld, matManaWorld;

	D3DXMatrixTransformation(&matHpWorld, &D3DXVECTOR3(53, 12, 0), NULL, &D3DXVECTOR3(m_fEnergyWidth, 1.f, 1.f),
		NULL, NULL, &D3DXVECTOR3(53, 12, 0));

	D3DXMatrixTransformation(&matManaWorld, &D3DXVECTOR3(720, 630, 0), NULL, &D3DXVECTOR3(m_fManaWidth, 1.f, 1.f),
		NULL, NULL, &D3DXVECTOR3(720, 630, 0));

	m_pHpFrame->GetChild()[0]->SetWorld(&matHpWorld);
	m_pManaFrame->GetChild()[0]->SetWorld(&matManaWorld);

	if (m_pHpFrame)
	{
		m_pHpFrame->Update();
	}

	if (m_pManaFrame)
	{
		m_pManaFrame->Update();
	}
}

void cPlayerGauge::Render()
{
	if (m_pHpFrame)
	{
		m_pHpFrame->Render(m_pSprite);
	}

	if (m_pManaFrame)
	{
		m_pManaFrame->Render(m_pSprite);
	}
}

void cPlayerGauge::SetEnergy(int width)
{
	m_fEnergyWidth = width / 1000.f;
}

void cPlayerGauge::SetMana(int width)
{
	m_fManaWidth = width / 1000.f;
}
