#include "stdafx.h"
#include "cTail.h"
#include "cAllocateHierarchy.h"

cTail::cTail()
	: m_pAlloc(nullptr)
	, m_pFrameRoot(nullptr)
	, m_pMesh(nullptr)
	, m_pBuffer(nullptr)
	, m_ft(0.1f)
	, m_bIsBlend(false)
	, m_fBlendTime(0.2f)
	, m_fPassedBlendTime(0.f)
{
	D3DXMatrixIdentity(&m_matTailTM);
}


cTail::~cTail()
{
	D3DXFrameDestroy(m_pFrameRoot, m_pAlloc);
	SAFE_DELETE(m_pAlloc);
	SAFE_RELEASE(m_pMesh);
}

void cTail::Setup(char* szFolderName, char* szFileName)
{
	m_pAlloc = new cAllocateHierarchy;

	m_pAlloc->SetFolder(szFolderName);

	m_sPath = szFolderName + std::string("/") + szFileName;

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

void cTail::Update()
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

	m_pAnimControl->AdvanceTime(g_pTimeManager->GetDeltaTime() / fAniTime, NULL);

	D3DXMATRIX matW;

	matW = m_matTailTM;
	SetupWorldMatrix(m_pFrameRoot, &matW);

	UpdateSkinnedMesh(m_pFrameRoot);

	int a = 0;
}

void cTail::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->LightEnable(0, true);
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//D3DXMatrixIdentity(&m_pFrame->TransformationMatrix);
	ST_BONE* pBone = (ST_BONE*)m_pFrameRoot;
	RecursiveFrameRender(pBone, &pBone->CombinedTransformationMatrix);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetTexture(0, nullptr);
}

void cTail::RecursiveFrameRender(D3DXFRAME* pFrame, D3DXMATRIX* pParentWorldTM)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	D3DXMATRIX matW;
	D3DXMatrixIdentity(&matW);

	matW = pFrame->TransformationMatrix * (*pParentWorldTM);
	pBone->CombinedTransformationMatrix = matW;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		for (size_t i = 0; i < pBoneMesh->dwNumSubset; ++i)
		{
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMaterial[i]);
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
		}
	}
	//�ڽ�
	if (pFrame->pFrameFirstChild)
	{
		RecursiveFrameRender(pFrame->pFrameFirstChild, &matW);
	}
	//����
	if (pFrame->pFrameSibling)
	{
		RecursiveFrameRender(pFrame->pFrameSibling, pParentWorldTM);
	}
}

void cTail::SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIX* pMatParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;

	if (pMatParent)
	{
		pBone->CombinedTransformationMatrix *= (*pMatParent);
	}

	if (pBone->pFrameSibling)
	{
		SetupWorldMatrix(pBone->pFrameSibling, pMatParent);
	}
	if (pBone->pFrameFirstChild)
	{
		SetupWorldMatrix(pBone->pFrameFirstChild, &pBone->CombinedTransformationMatrix);
	}
}

void cTail::SetupBoneMatrixPtrs(D3DXFRAME* pFrame)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.

	// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
	// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
	// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
	// ã�Ƽ� �����Ʈ������ �ɾ����.

	//��������� ��� �����ӿ� ���ؼ� ����.
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

void cTail::UpdateSkinnedMesh(D3DXFRAME* pFrame)
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

		//MeshData.pMesh�� ������Ʈ �����ش�.
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

void cTail::SetAnimationIndex(int nIndex)
{
	if (m_pAnimControl == NULL)
		return;

	LPD3DXANIMATIONSET pAnimSet = NULL;						//���ο� �ִϸ��̼��� ������ �ִϸ��̼� �� ������

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

DOUBLE cTail::GetAniTrackPeriod(int nIndex)
{
	DOUBLE fTime = 0.f;
	LPD3DXANIMATIONSET pAnimSet;
	m_pAnimControl->GetAnimationSet(nIndex, &pAnimSet);
	fTime = pAnimSet->GetPeriod();
	SAFE_RELEASE(pAnimSet);
	return fTime;
}