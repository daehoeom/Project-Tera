#include "stdafx.h"
#include "cLoadImage.h"


cLoadImage::cLoadImage()
	:cGameObject("Loading")
	, m_isDebugRender(true)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cLoadImage::~cLoadImage()
{
}

void cLoadImage::Update()
{
	
}

void cLoadImage::Render(LPD3DXSPRITE pSprite)
{
	if (m_isDebugRender)
	{
		float x, y, w, h;
		x = m_matWorld._41;
		y = m_matWorld._42;
		w = m_stSize.fWidth;
		h = m_stSize.fHeight;

		D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);
		std::vector<ST_RHWC_VERTEX> vecVertex;
		vecVertex.reserve(8);

		vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(x, y, 0, 1), c));
		vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(x + w, y, 0, 1), c));

		vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(x + w, y, 0, 1), c));
		vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(x + w, y + h, 0, 1), c));

		vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(x + w, y + h, 0, 1), c));
		vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(x, y + h, 0, 1), c));

		vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(x, y + h, 0, 1), c));
		vecVertex.push_back(ST_RHWC_VERTEX(D3DXVECTOR4(x, y, 0, 1), c));

		g_pD3DDevice->SetFVF(ST_RHWC_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 4, &vecVertex[0], sizeof(ST_RHWC_VERTEX));

	}
}