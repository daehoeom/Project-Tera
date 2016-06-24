#pragma once

#include "cUIObject.h"

class cUITextView : public cUIObject
{
protected:
	SYNTHESIZE(std::string, m_sText, Text);
	SYNTHESIZE(LPD3DXFONT, m_eFontType, FontType);
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwColor, TextColor);
public:
	cUITextView();
	virtual ~cUITextView();

	virtual void Render(LPD3DXSPRITE pSprite) override;
};

