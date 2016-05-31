#pragma once
class cAllocateHierarchy;
struct ST_BONE_MESH;

class cBody
{
	//XÆÄÀÏ
	cAllocateHierarchy*			m_pAlloc;
	LPD3DXFRAME					m_pFrameRoot;
	LPD3DXFRAME					m_pFrameRootOrigin;

	//string						
	std::string						m_sPath;
	LPD3DXANIMATIONCONTROLLER	m_pAnimControl;

	LPD3DXMESH					m_pMesh;
	LPD3DXBUFFER				m_pBuffer;
	std::vector<LPDIRECT3DTEXTURE9>	m_vecTexture;
	float						m_ft;

public:

	D3DXMATRIX					m_matNeckTM;
	D3DXMATRIX					m_matHairTM;
	D3DXMATRIX					m_matRootTM;


public:
	cBody();
	~cBody();
	void Setup(char* FolderName, char* FileName);
	void Update();
	void Render();
	void RecursiveFrameRender(D3DXFRAME* pParent, D3DXMATRIX* pParentWorldTM);
	void cBody::SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIX* pmatParent);
	void cBody::SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void cBody::UpdateSkinnedMesh(D3DXFRAME* pFrame);
	void cBody::GetNeckWorld(D3DXFRAME* pFrame, D3DXMATRIX* pParentTM);
	LPD3DXFRAME& cBody::GetFrameRoot();

	void SetNeckTM(D3DXMATRIX* neck) { m_matNeckTM = *neck; }
	D3DXMATRIX GetNeckTM() { return m_matNeckTM; }

	void SetHairTM(D3DXMATRIX* hair) { m_matHairTM = *hair; }
	D3DXMATRIX GetHairTM() { return m_matHairTM; }

	void SetRootTM(D3DXMATRIX* root) { m_matRootTM = *root; }
	D3DXMATRIX GetRootTM() { return m_matRootTM; }
};

