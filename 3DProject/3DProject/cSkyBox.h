#pragma once
class cSkyBox
{
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;
	float							m_fAngleX;
	float							m_fAngleY;
	LPDIRECT3DTEXTURE9				m_pTexture[6];
	std::vector<ST_PT_VERTEX>		m_vecVertex;
	D3DXMATRIXA16					m_matWorld;
public:
	cSkyBox();
	~cSkyBox();

	void Setup();
	void Render();
	void Update();
};

