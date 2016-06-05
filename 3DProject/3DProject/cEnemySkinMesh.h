#pragma once

class cAllocateHierarchy;
struct ST_BONE_MESH;

class cEnemySkinMesh
{
public:
	cEnemySkinMesh();
	~cEnemySkinMesh();

	void Setup(char* FolderName, char* FileName);
	void Update();
	void Render();
	void RecursiveFrameRender(D3DXFRAME* pParent, D3DXMATRIX* pParentWorldTM);
	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIX* pmatParent);
	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);
	void GetNeckWorld(D3DXFRAME* pFrame, D3DXMATRIX* pParentTM);
	void SetAnimationIndex(int nIndex);
	LPD3DXFRAME& GetFrameRoot();
	DOUBLE GetAniTrackPeriod(int nIndex);

	void SetRootTM(D3DXMATRIX* root) { m_matRootTM = *root; }
	D3DXMATRIX GetRootTM() { return m_matRootTM; }

	void SetWorld(D3DXMATRIX* world) { m_matWorld = *world; }
	D3DXMATRIX GetWorld() { return m_matWorld; }

	void SetLocal(D3DXMATRIX* local) { m_matLocal = *local; }
	D3DXMATRIX GetLocal() { return m_matLocal; }

private:
	//X파일
	cAllocateHierarchy*			m_pAlloc;
	LPD3DXFRAME					m_pFrameRoot;
	LPD3DXFRAME					m_pFrameRootOrigin;

	//string						
	std::string					m_sPath;
	LPD3DXANIMATIONCONTROLLER	m_pAnimControl;

	LPD3DXMESH					m_pMesh;
	LPD3DXBUFFER				m_pBuffer;
	std::vector<LPDIRECT3DTEXTURE9>	m_vecTexture;
	float						m_ft;

	D3DXMATRIX					m_matRootTM;
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matLocal;

	//보간
	bool						m_bIsBlend;
	float						m_fPassedBlendTime;
	float						m_fBlendTime;
};

