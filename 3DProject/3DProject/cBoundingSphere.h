#pragma once

#include "GameObject.h"

class cBoundingSphere : public GameObject
{
	LPD3DXMESH		sphereMesh;
	D3DMATERIAL9	stMtl;
	D3DXMATRIXA16	m_matWorld;
	bool			m_bWireDraw;		//와이어 프레임으로 그릴 것인지?
	float			m_fRadius;

public:
	cBoundingSphere();
	~cBoundingSphere();

	void Setup(D3DXVECTOR3* vCenter, float radius);
	void Update(D3DXMATRIXA16* matWorld);
	void Render();
	bool SetWireDraw(bool isDraw) { m_bWireDraw = isDraw; }

	float GetRadius() { return m_fRadius; }
	void SetRadius(float radius) { m_fRadius = radius; }
};

