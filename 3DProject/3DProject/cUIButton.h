#pragma once

#include "cUIObject.h"

class cUIButton;

class iUIButtonDelegate
{
public :
	virtual void OnClick(cUIButton* pSender) = 0;
	virtual void OnStayClick(cUIButton* pSender) = 0;
	virtual void OnChangeItem(cUIButton* pSender) = 0;
};



enum eButtonType
{
	E_TYPE_BUTTONSTAY,
	E_TYPE_BUTTONMOVE,
};

class cUIButton : public cUIObject
{
public:
	cUIButton();
	virtual ~cUIButton();

protected:

	SYNTHESIZE(iUIButtonDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(eButtonType, m_eType, ButtonType);

public:
	virtual void SetButtonTexture(std::string sFullPath);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

