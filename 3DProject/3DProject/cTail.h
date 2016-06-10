#pragma once

class cAllocateHierarchy;

class cTail
{
public:
	cTail();
	~cTail();

	void Setup(char* szFolderName, char* szFileName);
	void Update();
	void Render();
	void RecursiveFrameRender(D3DXFRAME* pFrame, D3DXMATRIX* pParentWorldTM);
	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIX* pMatParent);
	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);
	void SetAnimationIndex(int nIndex);
	DOUBLE GetAniTrackPeriod(int nIndex);

	void SetTailTM(D3DXMATRIX* tail) { m_matTailTM = *tail; }
	D3DXMATRIX GetTailTM() { return m_matTailTM; }

private:
	//X파일
	cAllocateHierarchy*					m_pAlloc;
	LPD3DXFRAME							m_pFrameRoot;
	LPD3DXFRAME							m_pFrameRootOrigin;

	//string
	std::string							m_sPath;
	LPD3DXANIMATIONCONTROLLER			m_pAnimControl;

	LPD3DXMESH							m_pMesh;
	LPD3DXBUFFER						m_pBuffer;
	std::vector<LPDIRECT3DTEXTURE9>		m_vecTexture;
	float								m_ft;

	LPD3DXFRAME							m_pFrameTail;

	D3DXMATRIX							m_matTailTM;

	//보간
	bool								m_bIsBlend;
	float								m_fPassedBlendTime;
	float								m_fBlendTime;

	int a = 0;
};

