#include "stdafx.h"
#include "cPlayerUI.h"
#include "cInventory.h"
#include "cEquipWindow.h"

cPlayerUI::cPlayerUI()
	: m_pInven(nullptr)
	, m_pEquip(nullptr)
{
	m_pInven = new cInventory;
	m_pEquip = new cEquipWindow;

	m_pInven->SetMemLink(m_pEquip);
	m_pEquip->SetMemLink(m_pInven);
}


cPlayerUI::~cPlayerUI()
{
	SAFE_DELETE(m_pEquip);
	SAFE_DELETE(m_pInven);
}

void cPlayerUI::Update()
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (m_pInven->GetInvenClose())
		{
			m_pInven->SetInvenClose(false);
		}

		else if (!m_pInven->GetInvenClose())
		{
			m_pInven->SetInvenClose(true);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (m_pEquip->GetEquipClose())
		{
			m_pEquip->SetEquipClose(false);
		}

		else if (!m_pEquip->GetEquipClose())
		{
			m_pEquip->SetEquipClose(true);
		}
	}

	if (!m_pInven->GetInvenClose())
	{
		m_pInven->Update();
	}

	if (!m_pEquip->GetEquipClose())
	{
		m_pEquip->Update();
	}
}

void cPlayerUI::Render()
{
	if (!m_pInven->GetInvenClose())
	{
		m_pInven->Render();
	}

	if (!m_pEquip->GetEquipClose())
	{
		m_pEquip->Render();
	}
}