#include "stdafx.h"
#include "cUITextView.h"


cUITextView::cUITextView() 
	:m_eFontType(nullptr)
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	fd.Height = 14;
	fd.Width = 10;
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, "°íµñÃ¼");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_eFontType);
}

cUITextView::~cUITextView()
{
	SAFE_RELEASE(m_eFontType);
}

void cUITextView::Render(LPD3DXSPRITE pSprite)
{
	RECT rc;

	SetRect(&rc, m_matWorld._41, m_matWorld._42, m_matWorld._41 + m_nWidth,
		m_matWorld._42 + m_nHeight);

	m_eFontType->DrawTextA(NULL, m_sText.c_str(), m_sText.length(), &rc,
		m_dwDrawTextFormat, m_dwColor);

	cUIObject::Render(pSprite);
}
