#pragma once
#include "cGameObject.h"

class cGrid : 
	public cGameObject
{
public:
	cGrid( int nLine = 30, float fInterval = 1.0f );
	virtual ~cGrid(void);

	virtual void Render( ) override;
	virtual void Update() override;

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	int							m_nNumLine;

};

