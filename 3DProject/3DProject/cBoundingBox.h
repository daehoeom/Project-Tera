#pragma once
#include "GameObject.h"

class cBoundingBox 
	: public GameObject
{
	LPD3DXMESH			m_pBox;
	D3DXMATRIXA16		m_matWorld;
	D3DMATERIAL9		stMtl;
	bool				m_bWireDraw;
	D3DXVECTOR3			m_vMin;
	D3DXVECTOR3			m_vMax;

public:
	cBoundingBox();
	cBoundingBox( const char* name );
	~cBoundingBox();

	void Setup(D3DXVECTOR3* vMin, D3DXVECTOR3* vMax);
	void Update(D3DXMATRIXA16* matWorld);
	void Render();

	D3DXVECTOR3 GetMinimum() { return m_vMin; }
	D3DXVECTOR3 GetMaximum(){ return m_vMax; }
};