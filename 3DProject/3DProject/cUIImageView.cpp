#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
{
}


cUIImageView::~cUIImageView()
{
}

void cUIImageView::SetViewTexture(std::string sFullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(sFullPath, &stImageInfo);

	m_nWidth = stImageInfo.Width;
	m_nHeight = stImageInfo.Height;
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	RECT rc;
	SetRect(&rc, 0, 0, m_nWidth, m_nHeight);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_matWorld);
	pSprite->Draw(m_pTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}