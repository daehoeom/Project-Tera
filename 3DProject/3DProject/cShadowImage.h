#pragma once
class cShadowImage
{
	std::vector<ST_PT_VERTEX> m_vecVertex;
	LPDIRECT3DTEXTURE9		  m_pTex;
	D3DXMATRIXA16			  m_matWorld;

public:
	cShadowImage(float xSize, float ySize);
	~cShadowImage();

	void Update(D3DXVECTOR3 vPos);
	void Render();
};

