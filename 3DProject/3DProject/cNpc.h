#pragma once

#include "cCollisionObject.h"

class cSkinnedMesh;
class cNpc : 
	public cCollisionObject
{
public:
	cNpc();
	virtual ~cNpc();

	void Setup(char* szFolder, char* szFile);
	virtual void Update() override;
	virtual void Render() override;

	void SetLocalHair(D3DXMATRIXA16* mat) { m_matLocalHair = *mat; }
	void SetLocalHead(D3DXMATRIXA16* mat) { m_matLocalHead = *mat; }
	void SetWorld(D3DXMATRIXA16* mat) { m_matWorld = *mat; }

	void SetType(eNpcType e) { m_sType = e; }
	eNpcType GetType() { return m_sType; }

private:
	std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;

	D3DXMATRIXA16		m_matWorld;
	D3DXMATRIX			m_matLocalHair;
	D3DXMATRIX			m_matLocalHead;
	
	float				m_fAngle;

	eNpcType			m_sType;
};

