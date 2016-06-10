#pragma once

class cAllocateHierarchy;

class cWeaponMesh
{
public:
	cWeaponMesh(void);
	~cWeaponMesh(void);

	void Setup(char* szFolder, char* szFile);
	void Update();
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	void Render(LPD3DXFRAME pFrame);
	void GetWeaponWorld(D3DXFRAME* pFrame, D3DXMATRIX* pParentTM);
	void SetWeapon(D3DXMATRIX* weapon) { m_matWeaponTM = *weapon; }
	D3DXMATRIX GetWeapon() { return m_matWeaponTM; }

	void SetWeaponWorld(D3DXMATRIX* weapon) { m_matWeaponMesh = *weapon; }
	D3DXMATRIX GetWeaponWorld() { return m_matWeaponMesh; }

	void GetWeaponkWorldTM(D3DXFRAME* pFrame, D3DXMATRIX* pParentTM);

private:
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);

private:
	cAllocateHierarchy*					m_pAlloc;
	LPD3DXFRAME							m_pFrameRoot;
	LPD3DXFRAME							m_pFrameRootOrigin;

	//string
	std::string							m_sPath;
	LPD3DXANIMATIONCONTROLLER			m_pAnimControl;

	LPD3DXMESH							m_pMesh;
	LPD3DXBUFFER						m_pBuffer;
	std::vector<LPDIRECT3DTEXTURE9>		m_vecTexture;

	D3DXMATRIX							m_matWeaponTM;
	D3DXMATRIX							m_matWeaponMesh;
};

