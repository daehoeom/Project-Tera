#pragma once

class cAllocateHierarchy;

class cFace
{
private:
	//XÆÄÀÏ
	cAllocateHierarchy*				m_pAlloc;
	LPD3DXFRAME						m_pFrameRoot;
	LPD3DXFRAME						m_pFrameRootOrigin;
	std::string						m_sPath;
	LPD3DXANIMATIONCONTROLLER		m_pAnimControl;

	LPD3DXMESH						m_pMesh;
	LPD3DXBUFFER					m_pBuffer;
	std::vector<LPDIRECT3DTEXTURE9>	m_vecTexture;
	float							m_ft;

	LPD3DXFRAME						m_pFrameNeck;

	D3DXMATRIX						m_matNeckTM;
	D3DXMATRIX						m_matHairTM;
public:
	cFace();
	~cFace();

	void Setup(char* szFolder, char* szFile);
	void Update();
	void Render();
	void RecursiveFrameRender(D3DXFRAME* pFrame, D3DXMATRIX* pParentWorldTM);
	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIX* pmatParent);
	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);

	void SetNeckTM(D3DXMATRIX* neck) { m_matNeckTM = *neck; }
	D3DXMATRIX GetNeckTM() { return m_matNeckTM; }

	void SetHairTM(D3DXMATRIX* hair) { m_matHairTM = *hair; }
	D3DXMATRIX GetHairTM() { return m_matHairTM; }
};

