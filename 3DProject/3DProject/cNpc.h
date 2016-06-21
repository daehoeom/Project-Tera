#pragma once

#include "cCollisionObject.h"

class cNpcSkinnedMesh;
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
	void SetLocal(D3DXMATRIXA16* mat) { m_matLocal = *mat; }

	void SetPos(D3DXVECTOR3 vPos) { m_vPos = vPos; }

	void SetType(eNpcType e) { m_sType = e; }
	eNpcType GetType() { return m_sType; }

private:
	std::vector<cNpcSkinnedMesh*>	m_vecSkinnedMesh;

	D3DXMATRIXA16		m_matWorld;
	D3DXMATRIXA16		m_matLocal;
	D3DXMATRIX			m_matLocalHair;
	D3DXMATRIX			m_matLocalHead;
	D3DXVECTOR3			m_vPos;

	float				m_fAngle;

	eNpcType			m_sType;
};

