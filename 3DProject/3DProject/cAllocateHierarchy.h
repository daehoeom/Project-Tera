#pragma once

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<LPDIRECT3DTEXTURE9> vecTexture;
	std::vector<D3DMATERIAL9>		vecMaterial;

	LPD3DXMESH				pWorkingMesh;			// 작업메쉬
	LPD3DXMESH				pOrigMesh;				// 원본 메쉬 CloneMeshFVF로 복사
	D3DXMATRIXA16**			ppBoneMatrixPtrs;		// 이 메쉬에 영향을 주는 프레임'들'의 월드매트릭스 포인터 배열
	D3DXMATRIXA16*			pBoneOffsetMatrices;	// 원본 메쉬를 로컬스페이스로 보내는 매트릭스들.

	DWORD					dwNumPaletteEntries;
	DWORD					dwMaxNumFaceInfls;
	DWORD					dwNumAttrGroups;
	LPD3DXBUFFER			pBufBoneCombos;
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	cAllocateHierarchy(void);
	~cAllocateHierarchy(void);

protected:
	std::string		m_sDirectory;
	D3DXVECTOR3		m_vMin;
	D3DXVECTOR3		m_vMax;
	DWORD			m_dwDefaultPaletteSize;
	DWORD			m_dwMaxPaletteSize;

public:
	/*SYNTHESIZE(std::string, m_sDirectory, Directory);
	SYNTHESIZE(D3DXVECTOR3, m_vMin, Min);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, Max);
	SYNTHESIZE(DWORD, m_dwDefaultPaletteSize, DefaultPaletteSize);
	SYNTHESIZE(DWORD, m_dwMaxPaletteSize, MaxPaletteSize);*/

	std::string GetDirectory() { return m_sDirectory; }
	void SetDirectory(std::string directory) { m_sDirectory = directory; }

	D3DXVECTOR3 GetMin() { return m_vMin; }
	void SetMin(D3DXVECTOR3 min) { m_vMin = min; }

	D3DXVECTOR3 GetMax() { return m_vMax; }
	void SetMax(D3DXVECTOR3 max) { m_vMax = max; }

	DWORD GetDefaultPaletteSize() { return m_dwDefaultPaletteSize; }
	void SetDefaultPaletteSize(DWORD df) { m_dwDefaultPaletteSize = df; }

	DWORD GetMaxPaletteSize() { return m_dwMaxPaletteSize; }
	void SetMaxPaletteSize(DWORD maxsize) { m_dwMaxPaletteSize = maxsize; }

	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name,
		LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;
};