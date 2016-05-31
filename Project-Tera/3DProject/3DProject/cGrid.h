#pragma once


class cGrid
{
public:
	cGrid( int nLine = 30, float fInterval = 1.0f );
	~cGrid(void);

	void Render();

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	int							m_nNumLine;

};

