#pragma once

#include "cCollisionObject.h"

class cBody;
class cHair;
class cFace;
class cBoundingSphere;

class cNpc : 
	public cCollisionObject
{
public:
	cNpc();
	~cNpc();

	void Setup(D3DXMATRIXA16* matWorld, char* szFolder, char* szFile);
	void Update();
	void Render();

private:
	cBody*				m_pBody;
	cHair*				m_pHair;
	cFace*				m_pFace;

	D3DXMATRIXA16		m_matWorld;

	float				m_fAngle;
	cBoundingSphere*	m_pBound;
};

