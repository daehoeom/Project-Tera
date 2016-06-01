#pragma once
class cMtlTex
{
protected:
	SYNTHESIZE_ADD_REF(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Mtl);

public:
	cMtlTex(void);
	~cMtlTex(void);
};

