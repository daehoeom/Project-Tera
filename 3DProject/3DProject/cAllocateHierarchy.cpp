#include "StdAfx.h"
#include "cAllocateHierarchy.h"


cAllocateHierarchy::cAllocateHierarchy(void)
{
}

cAllocateHierarchy::~cAllocateHierarchy(void)
{
}

STDMETHODIMP cAllocateHierarchy::CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	//*ppNewFrame = new D3DXFRAME_DR;
	ST_BONE* pFrame = new ST_BONE;
	pFrame->Name = nullptr;
	pFrame->pFrameFirstChild = nullptr;
	pFrame->pFrameSibling = nullptr;
	pFrame->pMeshContainer = nullptr;
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

	// TODO : 새로만든 노드에 이름을 복사
	if (Name)
	{
		pFrame->Name = new char[strlen(Name) + 1];
		strcpy(pFrame->Name, Name);
	}
	*ppNewFrame = pFrame;
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer(
	THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;
	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		std::string sFile(pMaterials[i].pTextureFilename);
		std::string sPath = sFolderName + std::string("/") + std::string(pMaterials[i].pTextureFilename);
		LPDIRECT3DTEXTURE9 pTex = g_pTextureManager->GetTexture((sPath).c_str());
		pBoneMesh->vecMaterial.push_back(pMaterials[i].MatD3D);
		pBoneMesh->vecTexture.push_back(pTex);
	}

	if (pMeshData && D3DXMESHTYPE_MESH == pMeshData->Type)
	{
		pBoneMesh->MeshData.Type = pMeshData->Type;
		pBoneMesh->MeshData.pMesh = pMeshData->pMesh;
		pMeshData->pMesh->GetAttributeTable(0, &pBoneMesh->dwNumSubset);

		pMeshData->pMesh->AddRef();
	}
	if (pSkinInfo)
	{
		pSkinInfo->Clone(&pBoneMesh->pSkinInfo);
		if (pMeshData && D3DXMESHTYPE_MESH == pMeshData->Type)
		{
			pMeshData->pMesh->CloneMeshFVF(
				pMeshData->pMesh->GetOptions(),
				pMeshData->pMesh->GetFVF(),
				g_pD3DDevice,
				&pBoneMesh->pOrigMesh);
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			
			pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];
			pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
			pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];

			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
			}
		}
	}

	(*ppNewMeshContainer) = pBoneMesh;
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;
	if (pBone->Name)
	{
		SAFE_DELETE_ARRAY(pBone->Name);
	}

	delete pFrameToFree;
	
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;
	SAFE_RELEASE(pBoneMesh->pSkinInfo);
	SAFE_RELEASE(pBoneMesh->MeshData.pMesh);
	SAFE_RELEASE(pBoneMesh->pOrigMesh);

	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->pCurrentBoneMatrices);

	delete pBoneMesh;
	return S_OK;
}

