#pragma once
class cSkyBox
{
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;
	float							m_fAngleX;
	float							m_fAngleY;
	LPDIRECT3DTEXTURE9				m_pTexture;
	std::vector<ST_PT_VERTEX>		m_vecVertex;
public:
	cSkyBox();
	~cSkyBox();

	void Setup();
	void Render();
	void Update();
};

