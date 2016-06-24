#pragma once

#include "cUIButton.h"

class cUIObject;
class cEquipWindow;

class cInventory : public iUIButtonDelegate
{
	cEquipWindow* m_pEquip;
	LPD3DXSPRITE m_pSprite;

	SYNTHESIZE(cUIObject*, m_pUIRoot, Root);
	SYNTHESIZE(bool, m_bInventoryClose, InvenClose);
public:
	cInventory();
	~cInventory();

	void Update();
	void Render();

	void SetMemLink(cEquipWindow* pEquip) { m_pEquip = pEquip; }

	virtual void OnClick(cUIButton* pSender) override;
	virtual void OnStayClick(cUIButton* pSender) override;
	virtual void OnChangeItem(cUIButton* pSender) override;
};

