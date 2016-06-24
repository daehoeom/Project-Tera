#include "stdafx.h"
#include "cInventory.h"
#include "cUIButton.h"
#include "cUIObject.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cEquipWindow.h"

cInventory::cInventory()
	: m_pSprite(nullptr)
	, m_pUIRoot(nullptr)
{
	cUIButton* pView = new cUIButton;
	pView->SetButtonTexture("./CH/UIImage/牢亥配府.png");
	pView->SetPosition(D3DXVECTOR3(850, 50, 0));
	pView->SetButtonType(E_TYPE_BUTTONMOVE);
	pView->SetDelegate(this);
	pView->SetButtonTag(E_TAG_MOVE);
	m_pUIRoot = pView;

	cUITextView* pTextView = new cUITextView;
	pTextView->SetText("0");
	pTextView->SetPosition(D3DXVECTOR3(250, 390, 0));
	pTextView->SetSize(30, 30);
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 255));
	pTextView->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pUIRoot->AddChild(pTextView);

	cUIButton* pButton = new cUIButton;
	pButton->SetButtonTexture("./CH/UIImage/ESC.tga");
	pButton->SetPosition({ 350, 40, 0 });
	pButton->SetButtonTag(E_TAG_CLOSE);
	pButton->SetDelegate(this);
	m_pUIRoot->AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetButtonTexture("./CH/UIImage/规绢备2.tga");
	pButton->SetPosition({ 19, 85, 0 });
	pButton->SetButtonTag(E_TAG_ITEM2);
	pButton->SetDelegate(this);
	m_pUIRoot->AddChild(pButton);

	pButton = new cUIButton;
	pButton->SetButtonTexture("./CH/UIImage/规绢备3.tga");
	pButton->SetPosition({ 62, 85, 0 });
	pButton->SetButtonTag(E_TAG_ITEM3);
	pButton->SetDelegate(this);
	m_pUIRoot->AddChild(pButton);

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}

cInventory::~cInventory()
{
	SAFE_RELEASE(m_pSprite);

	if (m_pUIRoot)
	{
		m_pUIRoot->Destroy();
		m_pUIRoot = nullptr;
	}
}

void cInventory::Update()
{
	m_pUIRoot->Update();
}

void cInventory::Render()
{
	m_pUIRoot->Render(m_pSprite);
}

void cInventory::OnClick(cUIButton* pSender)
{
	if (pSender->GetButtonTag() == E_TAG_CLOSE)
	{
		m_bInventoryClose = true;
	}
}

void cInventory::OnStayClick(cUIButton* pSender)
{
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

void cInventory::OnChangeItem(cUIButton* pSender)
{
	if (pSender->GetButtonTag() == E_TAG_ITEM1 || pSender->GetButtonTag() == E_TAG_ITEM2 
		|| pSender->GetButtonTag() == E_TAG_ITEM3)
	{
		LPDIRECT3DTEXTURE9 pTex;
		pTex = pSender->GetTexture();
		pSender->SetTexture(m_pEquip->GetRoot()->GetChild()[2]->GetTexture());
		m_pEquip->GetRoot()->GetChild()[2]->SetTexture(pTex);

		eButtonTag e;
		e = pSender->GetButtonTag();
		pSender->SetButtonTag(m_pEquip->GetRoot()->GetChild()[2]->GetButtonTag());
		m_pEquip->GetRoot()->GetChild()[2]->SetButtonTag(e);
	}
}