#pragma once

#include "cUIButton.h"

class cUIObject;
class cInventory;

class cEquipWindow : public iUIButtonDelegate
{
	cInventory*  m_pInven;
	LPD3DXSPRITE m_pSprite;

	SYNTHESIZE(cUIObject*, m_pUIRoot, Root);
	SYNTHESIZE(bool, m_bEquipClose, EquipClose);

public:
	cEquipWindow();
	~cEquipWindow();

	void Update();
	void Render();

	void SetMemLink(cInventory* pInven) { m_pInven = pInven; }

	virtual void OnClick(cUIButton* pSender) override;
	virtual void OnStayClick(cUIButton* pSender) override;
	virtual void OnChangeItem(cUIButton* pSender) override;
};

