#pragma once

#include "cUIObject.h"

class cUIImageView : public cUIObject
{
public:
	cUIImageView();
	virtual ~cUIImageView();

	virtual void SetViewTexture(std::string sFullPath);
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

