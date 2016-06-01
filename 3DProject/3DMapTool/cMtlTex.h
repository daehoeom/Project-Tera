#pragma once
#include "cObject.h"

class cMtlTex : public cObject
{
protected:
	SYNTHESIZE_ADD_REF(LPDIRECT3DTEXTURE9, m_pTexture, Texture)
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Mtl)
	SYNTHESIZE(DWORD, m_dwAttrID, AttrID)

public:
	cMtlTex(void);
	~cMtlTex(void);
};

