#pragma once

class cAllocateHierarchy;
struct ST_BONE_MESH;

class cBody
{
public:
	cBody();
	~cBody();

	void Setup(char* szFullPath);
	void Update();
	void Render();
	void RecursiveFrameRender(D3DXFRAME* pFrame, D3DXMATRIXA16* pParentWorldTM);
	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pMatParent);
	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);
	void GetNeckWorld(D3DXFRAME* pFrame, D3DXMATRIXA16* pParentTM);
	void CalcCollisionSphere(ST_BONE_MESH* pBoneMesh);
	void RenderCollisionSphere(ST_BONE_MESH* pBoneMesh);
	LPD3DXFRAME& GetFrameRoot();
	
public:
	D3DXMATRIXA16						m_matNeckTM;
	D3DXMATRIXA16						m_matHairTM;
	D3DXMATRIXA16						m_matRootTM;

private:
	//X파일
	cAllocateHierarchy*					m_pAlloc;
	LPD3DXFRAME							m_pFrameRoot;
	LPD3DXFRAME							m_pFrameRootOrigin;

	//string		
	std::string							m_pPath;			//파일 경로
	LPD3DXANIMATIONCONTROLLER			m_pAnimControl;		//애니메이션 컨트롤러

	LPD3DXMESH							m_pMesh;
	LPD3DXBUFFER						m_pBuffer;
	std::vector<LPDIRECT3DTEXTURE9>		m_vecTexture;
	float								m_ft;

	

};

