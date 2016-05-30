#include "stdafx.h"
#include "cBody.h"
#include "cAllocateHierarchy.h"

cBody::cBody()
	: m_pAlloc(nullptr)
	, m_pFrameRoot(nullptr)
	, m_pMesh(nullptr)
	, m_pBuffer(nullptr)
	, m_ft(0.1f)
{
	D3DXMatrixIdentity(&m_matNeckTM);
	D3DXMatrixIdentity(&m_matRootTM);
	D3DXMatrixIdentity(&m_matHairTM);
}


cBody::~cBody()
{
	D3DXFrameDestroy(m_pFrameRoot, m_pAlloc);
	SAFE_DELETE(m_pAlloc);
	SAFE_RELEASE(m_pMesh);
}

void cBody::Setup(char* szFullPath)
{
	m_pAlloc = new cAllocateHierarchy;

	m_pPath = std::string(szFullPath);

	HRESULT hr = D3DXLoadMeshHierarchyFromX(m_pPath.c_str(),
		D3DXMESH_MANAGED, g_pD3DDevice, m_pAlloc, NULL,
		&m_pFrameRoot, &m_pAnimControl);

	assert(hr == S_OK);
	SetupBoneMatrixPtrs((ST_BONE*)m_pFrameRoot);

	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);
}

void cBody::Update()
{
	m_pAnimControl->AdvanceTime(0.0075f, NULL);
	GetNeckWorld(m_pFrameRoot, nullptr);
	UpdateSkinnedMesh(m_pFrameRoot);
}

void cBody::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->LightEnable(0, true);
	ST_BONE* pBone = (ST_BONE*)m_pFrameRoot;
	RecursiveFrameRender(pBone, &pBone->CombinedTransformationMatrix);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetTexture(0, nullptr);
}

void cBody::RecursiveFrameRender(D3DXFRAME* pFrame, D3DXMATRIXA16* pParentWorldTM)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);

	//자신의 월드 매트릭스는 부모의 월드 매트릭스 * 자신의 매트릭스 월드
	matW = pFrame->TransformationMatrix * (*pParentWorldTM);

	//자신의 월드매트릭스를 설정한다.
	pBone->CombinedTransformationMatrix = matW;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		for (size_t i = 0; i < pBoneMesh->dwNumSubset; i++)
		{
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMaterial[i]);
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
			g_pD3DDevice->SetTexture(0, NULL);
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

void cBody::SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pMatParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;

	if (pMatParent)
	{
		pBone->CombinedTransformationMatrix *= (*pMatParent);
	}

	//자식
	if (pBone->pFrameSibling)
	{
		SetupWorldMatrix(pBone->pFrameSibling, pMatParent);
	}
	if (pBone->pFrameFirstChild)
	{
		SetupWorldMatrix(pBone->pFrameFirstChild, &pBone->CombinedTransformationMatrix);
	}
}

void cBody::SetupBoneMatrixPtrs(D3DXFRAME* pFrame)
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

void cBody::UpdateSkinnedMesh(D3DXFRAME* pFrame)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;


	if (pBoneMesh)
	{
		DWORD nNumBones = pBoneMesh->pSkinInfo->GetNumBones();
		for (size_t i = 0; i < nNumBones; ++i)
		{
			pBoneMesh->pCurret[i] = pBoneMesh->pBoneOffsetMatrices[i] * (*pBoneMesh->ppBoneMatrixPtrs[i]);
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;
		//D3DXVECTOR3* dest = NULL;
		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		//MeshData.pMesh을 업데이트 시켜준다.
		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

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

void cBody::GetNeckWorld(D3DXFRAME* pFrame, D3DXMATRIXA16* pParentTM)
{
}

void cBody::CalcCollisionSphere(ST_BONE_MESH* pBoneMesh)
{
}

void cBody::RenderCollisionSphere(ST_BONE_MESH* pBoneMesh)
{
}

LPD3DXFRAME& cBody::GetFrameRoot()
{
}

