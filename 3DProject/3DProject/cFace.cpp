#include "stdafx.h"
#include "cFace.h"
#include "cAllocateHierarchy.h"


cFace::cFace()
	: m_pAlloc(nullptr)
	, m_pFrameRoot(nullptr)
	, m_pMesh(nullptr)
	, m_pBuffer(nullptr)
	, m_ft(0.1f)
	, m_bIsBlend(false)
	, m_fBlendTime(0.2f)
	, m_fPassedBlendTime(0.f)
{
}


cFace::~cFace()
{
	D3DXFrameDestroy(m_pFrameRoot, m_pAlloc);
	SAFE_DELETE(m_pAlloc);
	SAFE_RELEASE(m_pMesh);
}

void cFace::Setup(char* szFolder, char* szFile)
{
	std::string folder = (std::string)szFolder;
	std::string file = (std::string)szFile;

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

void cFace::Update()
{
	if (m_bIsBlend)
	{
		m_fPassedBlendTime += g_pTimeManager->GetDeltaTime();

		if (m_fPassedBlendTime > m_fBlendTime)
		{
			m_bIsBlend = false;
			m_pAnimControl->SetTrackWeight(0, 1.f);
			m_pAnimControl->SetTrackEnable(1, false);
			m_fPassedBlendTime = 0.f;
		}

		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimControl->SetTrackWeight(0, fWeight);
			m_pAnimControl->SetTrackWeight(1, 1.f - fWeight);
		}
	}

	m_pAnimControl->AdvanceTime(fAniTime, NULL);

	D3DXMATRIX matW;
	matW = m_matNeckTM;
	SetupWorldMatrix(m_pFrameRoot, &matW);

	UpdateSkinnedMesh(m_pFrameRoot);
}

void cFace::RecursiveFrameRender(D3DXFRAME* pFrame, D3DXMATRIX* pParentWorldTM)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	D3DXMATRIX matW;
	D3DXMatrixIdentity(&matW);

	matW = pFrame->TransformationMatrix * (*pParentWorldTM);
	pBone->CombinedTransformationMatrix = matW;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		//g_pD3DDevice->SetTexture(0, pFrame->pMeshContainer->pMaterials);
		for (size_t i = 0; i < pBoneMesh->dwNumSubset; ++i)
		{
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMaterial[i]);
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
		}
	}
	//자식
	if (pFrame->pFrameFirstChild)
	{
		RecursiveFrameRender(pFrame->pFrameFirstChild, &matW);
	}
	//형제
	if (pFrame->pFrameSibling)
	{
		RecursiveFrameRender(pFrame->pFrameSibling, pParentWorldTM);
	}
}

void cFace::SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIX* pmatParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;

	if (pmatParent)
	{
		pBone->CombinedTransformationMatrix *= (*pmatParent);
	}

	if (pBone->pFrameSibling)
	{
		SetupWorldMatrix(pBone->pFrameSibling, pmatParent);
	}
	if (pBone->pFrameFirstChild)
	{
		SetupWorldMatrix(pBone->pFrameFirstChild, &pBone->CombinedTransformationMatrix);
	}
}

void cFace::SetupBoneMatrixPtrs(D3DXFRAME* pFrame)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

	if (pBoneMesh)
	{
		if (pBoneMesh->pSkinInfo)
		{
			DWORD nNumBones = pBoneMesh->pSkinInfo->GetNumBones();

			std::string sBoneName;
			for (size_t i = 0; i < nNumBones; ++i)
			{
				sBoneName = pBoneMesh->pSkinInfo->GetBoneName(i);
				ST_BONE* pFindedBone = (ST_BONE*)D3DXFrameFind(m_pFrameRoot, sBoneName.c_str());
				pBoneMesh->ppBoneMatrixPtrs[i] = &pFindedBone->CombinedTransformationMatrix;
				//pTargetBone->matWorldTM = pTargetBone->TransformationMatrix * ((ST_BONE*)m_pFrameRoot)->matWorldTM;
			}
		}
	}
	if (pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pBone->pFrameSibling);
	}
	if (pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pBone->pFrameFirstChild);
	}
}

void cFace::UpdateSkinnedMesh(D3DXFRAME* pFrame)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

	if (pBoneMesh)
	{
		DWORD nNumBones = pBoneMesh->pSkinInfo->GetNumBones();
		for (size_t i = 0; i < nNumBones; ++i)
		{
			pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * (*pBoneMesh->ppBoneMatrixPtrs[i]);
		}
		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		//MeshData.pMesh을 업데이트 시켜준다.
		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}
	if (pBone->pFrameSibling)
	{
		UpdateSkinnedMesh(pBone->pFrameSibling);
	}
	if (pBone->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pBone->pFrameFirstChild);
	}
}

void cFace::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->LightEnable(0, true);
	ST_BONE* pBone = (ST_BONE*)m_pFrameRoot;
	RecursiveFrameRender(pBone, &pBone->CombinedTransformationMatrix);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetTexture(0, nullptr);
}

void cFace::SetAnimationIndex(int nIndex)
{
	if (m_pAnimControl == NULL)
		return;

	LPD3DXANIMATIONSET pAnimSet = NULL;						//새로운 애니메이션을 저장할 애니메이션 셋 포인터

	D3DXTRACK_DESC desc;
	m_pAnimControl->GetTrackDesc(0, &desc);

	m_pAnimControl->GetTrackAnimationSet(0, &pAnimSet);
	m_pAnimControl->SetTrackAnimationSet(1, pAnimSet);

	m_pAnimControl->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimControl->SetTrackAnimationSet(0, pAnimSet);
	m_pAnimControl->SetTrackPosition(0, 0.f);
	m_pAnimControl->SetTrackDesc(1, &desc);

	m_bIsBlend = true;

	SAFE_RELEASE(pAnimSet);
}

DOUBLE cFace::GetAniTrackPeriod(int nIndex)
{
	DOUBLE fTime = 0.f;
	LPD3DXANIMATIONSET pAnimSet;
	m_pAnimControl->GetAnimationSet(nIndex, &pAnimSet);
	fTime = pAnimSet->GetPeriod();
	SAFE_RELEASE(pAnimSet);
	return fTime;
}