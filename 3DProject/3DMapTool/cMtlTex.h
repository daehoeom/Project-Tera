#pragma once
class cMtlTex
{
public:
	cMtlTex(void);
	~cMtlTex(void);

protected:
	SYNTHESIZE_PASS_BY_REF(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Mtl);
};

