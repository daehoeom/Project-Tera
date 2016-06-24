#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_pParent(nullptr)
	, m_vPosition({0, 0, 0})
	, m_nWidth(0)
	, m_nHeight(0)
	, m_pTexture(nullptr)
	, m_eTag(E_TAG_NONE)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cUIObject::~cUIObject()
{
}

void cUIObject::AddChild(cUIObject* pChild)
{
	pChild->m_pParent = this;
	m_vecChild.push_back(pChild);
}

void cUIObject::SetSize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
}

void cUIObject::Update()
{
	UpdateWorldTM();
	UpdateChildren();
}

void cUIObject::UpdateWorldTM()
{
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_vPosition.x;
		m_matWorld._42 += m_pParent->m_vPosition.y;
		m_matWorld._43 += m_pParent->m_vPosition.z;
	}
}

void cUIObject::UpdateChildren()
{
	for each(auto p in m_vecChild)
	{
		p->Update();
	}
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	m_Rc.left = m_matWorld._41;
	m_Rc.top = m_matWorld._42;

	m_Rc.right = m_Rc.left + m_nWidth;
	m_Rc.bottom = m_Rc.top + m_nHeight;

	for each(auto p in m_vecChild)
	{
		p->Render(pSprite);
	}
}

void cUIObject::Destroy()
{
	SAFE_RELEASE(m_pTexture);

	for each(auto p in m_vecChild)
	{
		SAFE_RELEASE(p);
	}
	Release();
}