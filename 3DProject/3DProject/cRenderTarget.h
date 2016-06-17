#pragma once
class cRenderTarget
{
	LPDIRECT3DTEXTURE9 m_pRenderTargetTex;
	LPDIRECT3DSURFACE9 m_pRenderTargetSurf;
	LPDIRECT3DSURFACE9 m_pOrigSurf;
	LPDIRECT3DSURFACE9 m_pOrigStencil;

public:
	cRenderTarget();
	~cRenderTarget();

	void CreateRenderTarget(const int _iW, const int _iH);
	void DeleteRenderTarget();
	void StartRenderTarget();
	void EndRenderTarget();
};

