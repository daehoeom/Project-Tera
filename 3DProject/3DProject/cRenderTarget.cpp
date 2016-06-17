#include "stdafx.h"
#include "cRenderTarget.h"


cRenderTarget::cRenderTarget()
{
}


cRenderTarget::~cRenderTarget()
{
}

void cRenderTarget::CreateRenderTarget(const int _iW, const int _iH)
{
	g_pD3DDevice->CreateTexture(_iW, _iH, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F,
		D3DPOOL_DEFAULT, &m_pRenderTargetTex, NULL);

	g_pD3DDevice->CreateDepthStencilSurface(_iW, _iH, D3DFMT_D24X8, D3DMULTISAMPLE_NONE,
		0, TRUE, &m_pRenderTargetSurf, NULL);
}

void cRenderTarget::DeleteRenderTarget()
{
	SAFE_RELEASE(m_pRenderTargetTex);
	SAFE_RELEASE(m_pRenderTargetSurf);
}

void cRenderTarget::StartRenderTarget()
{
	g_pD3DDevice->GetRenderTarget(0, &m_pOrigSurf);
	g_pD3DDevice->GetDepthStencilSurface(&m_pOrigStencil);
	LPDIRECT3DSURFACE9 pTargetSurf;
	m_pRenderTargetTex->GetSurfaceLevel(0, &pTargetSurf);
	g_pD3DDevice->SetRenderTarget(0, pTargetSurf);
	SAFE_RELEASE(pTargetSurf);
	g_pD3DDevice->SetDepthStencilSurface(m_pRenderTargetSurf);

	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), 0xffffff, 1.f, 0);
}

void cRenderTarget::EndRenderTarget()
{
	g_pD3DDevice->SetRenderTarget(0, m_pOrigSurf);
	g_pD3DDevice->SetDepthStencilSurface(m_pOrigStencil);
	SAFE_RELEASE(m_pOrigSurf);
	SAFE_RELEASE(m_pOrigStencil);
}