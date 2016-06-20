#include "stdafx.h"
#include "cShadowImage.h"


cShadowImage::cShadowImage(float xSize, float ySize)
	:m_pTex(nullptr)
{
	m_vecVertex.resize(6);
	m_vecVertex[0].p = D3DXVECTOR3(-xSize, 0, 0);
	m_vecVertex[0].t = D3DXVECTOR2(0, 1);

	m_vecVertex[1].p = D3DXVECTOR3(-xSize, 0, ySize);
	m_vecVertex[1].t = D3DXVECTOR2(0, 0);

	m_vecVertex[2].p = D3DXVECTOR3(xSize, 0, ySize);
	m_vecVertex[2].t = D3DXVECTOR2(1, 0);

	m_vecVertex[3].p = D3DXVECTOR3(-xSize, 0, 0);
	m_vecVertex[3].t = D3DXVECTOR2(0, 1);

	m_vecVertex[4].p = D3DXVECTOR3(xSize, 0, ySize);
	m_vecVertex[4].t = D3DXVECTOR2(1, 0);

	m_vecVertex[5].p = D3DXVECTOR3(xSize, 0, 0);
	m_vecVertex[5].t = D3DXVECTOR2(1, 1);

	m_pTex = g_pTextureManager->GetTexture("./CH/Shadow/Shadow.tga");

	D3DXMatrixIdentity(&m_matWorld);
}


cShadowImage::~cShadowImage()
{
	SAFE_RELEASE(m_pTex);
}

void cShadowImage::Update(D3DXVECTOR3 vPos)
{	
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y, vPos.z);

	m_matWorld =  matT;
}

void cShadowImage::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_pTex);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex[0], sizeof(ST_PT_VERTEX));
}