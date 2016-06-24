#include "stdafx.h"
#include "cEquipWindow.h"
#include "cInventory.h"
#include "cUIButton.h"
#include "cUIObject.h"
#include "cUIImageView.h"
#include "cUITextView.h"

cEquipWindow::cEquipWindow()
	: m_pInven(nullptr)
	, m_pUIRoot(nullptr)
	, m_bEquipClose(false)
	, m_pSprite(nullptr)
{
	cUIButton* pMain = new cUIButton;
	pMain->SetButtonTexture("./CH/UIImage/장비칸.png");
	pMain->SetPosition({ 100, 50, 0 });
	pMain->SetDelegate(this);
	pMain->SetButtonType(E_TYPE_BUTTONMOVE);
	pMain->SetButtonTag(E_TAG_MOVE);
	m_pUIRoot = pMain;

	cUITextView* pTextView = new cUITextView;
	pTextView->SetText("엘린짜능");
	pTextView->SetPosition({ 250, 20, 0 });
	pTextView->SetSize(50, 30);
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 255));
	pTextView->SetDrawTextFormat(DT_LEFT | DT_VCENTER | DT_WORDBREAK);
	m_pUIRoot->AddChild(pTextView);

	cUIButton* pButton = new cUIButton;
	pButton->SetButtonTexture("./CH/UIImage/ESC.tga");
	pButton->SetPosition({ 350, 20, 0 });
	pButton->SetButtonTag(E_TAG_CLOSE);
	pButton->SetDelegate(this);
	m_pUIRoot->AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetButtonTexture("./CH/UIImage/방어구1.tga");
	pButton->SetPosition({ 172, 237, 0 });
	pButton->SetButtonTag(E_TAG_ITEM1);
	pButton->SetDelegate(this);
	m_pUIRoot->AddChild(pButton);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}


cEquipWindow::~cEquipWindow()
{
	SAFE_RELEASE(m_pSprite);

	if (m_pUIRoot)
	{
		m_pUIRoot->Destroy();
		m_pUIRoot = nullptr;
	}
}

void cEquipWindow::Update()
{
	m_pUIRoot->Update();
}

void cEquipWindow::Render()
{
	m_pUIRoot->Render(m_pSprite);
}

void cEquipWindow::OnClick(cUIButton* pSender)
{
	if (pSender->GetButtonTag() == E_TAG_CLOSE)
	{
		m_bEquipClose = true;
	}
}

void cEquipWindow::OnStayClick(cUIButton* pSender)
{
	//인벤토리창이 업데이트가 되지 않으면 움직임 가능
	if (pSender->GetButtonTag() == E_TAG_MOVE)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		float x = pSender->GetPosition().x;
		float y = pSender->GetPosition().y;

		x += pt.x - ptPrev.x;
		y += pt.y - ptPrev.y;
		pSender->SetPosition(D3DXVECTOR3(x, y, 0));

		ptPrev = pt;
	}
}

void cEquipWindow::OnChangeItem(cUIButton* pSender)
{
}