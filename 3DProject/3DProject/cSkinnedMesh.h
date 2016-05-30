#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	~cSkinnedMesh(void);

	void UpdateAndRender();
	void SetAnimationIndex(int nIndex);

	void SetRandomTrackPosition(); // 테스트용
	void SetPosition(D3DXVECTOR3 v)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter = v;
	}
	
	ST_SPHERE* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}

private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();

private:
	//하나만 생성
	ST_BONE*					m_pRootFrame;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	ST_SPHERE					m_stBoundingSphere;

	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXVECTOR3					m_vPosition;
};

