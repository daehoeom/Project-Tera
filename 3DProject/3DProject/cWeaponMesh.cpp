#include "stdafx.h"
#include "cWeaponMesh.h"
#include "cAllocateHierarchy.h"

cWeaponMesh::cWeaponMesh()
	: m_pAlloc(NULL)
	, m_pAnimControl(NULL)
{
	D3DXMatrixIdentity(&m_matWeaponTM);
	D3DXMatrixIdentity(&m_matWeaponMesh);
}


cWeaponMesh::~cWeaponMesh()
{
	D3DXFrameDestroy(m_pFrameRoot, m_pAlloc);
	SAFE_DELETE(m_pAlloc);
	SAFE_RELEASE(m_pMesh);
	int a = 0;
}

void cWeaponMesh::Setup(char* szFolder, char* szFile)
{
	m_pAlloc = new cAllocateHierarchy;

	m_pAlloc->SetFolder(szFolder);

	m_sPath = szFolder + std::string("/") + szFile;

	HRESULT hr = D3DXLoadMeshHierarchyFromX(m_sPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		m_pAlloc,
		NULL,
		&m_pFrameRoot,
		&m_pAnimControl);
	assert(hr == S_OK);
	SetupBoneMatrixPtrs((ST_BONE*)m_pFrameRoot);
	D3DXMATRIX matW;
	D3DXMatrixIdentity(&matW);
}

void cWeaponMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;

	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;
	if (pParent)
	{
		pBone->CombinedTransformationMatrix *= ((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}
	if (pBone->pFrameFirstChild)
	{
		Update(pBone->pFrameFirstChild, pBone);
	}
	if (pBone->pFrameSibling)
	{
		Update(pBone->pFrameSibling, pParent);
	}
}

void cWeaponMesh::Update()
{
	Update(m_pFrameRoot, NULL);
	UpdateSkinnedMesh(m_pFrameRoot);
}

void cWeaponMesh::Render(LPD3DXFRAME pFrame)
{
	ST_BONE* pBone = NULL;

	if (pFrame)
		pBone = (ST_BONE*)pFrame;
	else
		pBone = (ST_BONE*)m_pFrameRoot;

	D3DXMATRIXA16 matR, matT, matWorld;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(pBone->CombinedTransformationMatrix * m_matWeaponTM));
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
	if (pBoneMesh)
	{
		for (size_t i = 0; i < pBoneMesh->vecTexture.size(); ++i)
		{
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMaterial[i]);
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
		}
	}
	if (pBone->pFrameFirstChild)
	{
		Render(pBone->pFrameFirstChild);
	}
	if (pBone->pFrameSibling)
	{
		Render(pBone->pFrameSibling);
	}
}

void cWeaponMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pFrameRoot, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &pBone->CombinedTransformationMatrix;
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void cWeaponMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				pBoneMesh->pCurrentBoneMatrices[i] =
					pBoneMesh->pBoneOffsetMatrices[i] *
					*(pBoneMesh->ppBoneMatrixPtrs[i]);
			}

			BYTE* src = NULL;
			BYTE* dest = NULL;

			pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

			//MeshData.pMesh을 업데이트 시켜준다.
			pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}

void cWeaponMesh::GetWeaponkWorldTM(D3DXFRAME* pFrame, D3DXMATRIX* pParentTM)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	
	if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Lance33_SM"));
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matWeaponMesh = pBone->CombinedTransformationMatrix;
	}

	//-180 180 180
	if (pFrame->pFrameSibling)
	{
		GetWeaponkWorldTM(pFrame->pFrameSibling, &pBone->CombinedTransformationMatrix);
	}
	if (pFrame->pFrameFirstChild)
	{
		GetWeaponkWorldTM(pFrame->pFrameFirstChild, &pBone->CombinedTransformationMatrix);
	}
}