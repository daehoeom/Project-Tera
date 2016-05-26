#pragma once


class cGrid
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	int							m_nNumLine;

public:
	cGrid(void);
	~cGrid(void);

	void Setup(int nLine = 30, float fInterval = 1.0f);
	void Render();
};

