#include "stdafx.h"
#include "cBody.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"


cBody::cBody()
	: m_pAlloc(nullptr)
	, m_pFrameRoot(nullptr)
	, m_pMesh(nullptr)
	, m_pBuffer(nullptr)
	, m_ft(0.1f)
	, m_bIsBlend(false)
	, m_fBlendTime(0.2f)
	, m_fPassedBlendTime(0.f)
{
	D3DXMatrixIdentity(&m_matNeckTM);
	D3DXMatrixIdentity(&m_matHairTM);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matWeaponBackTM);
	D3DXMatrixIdentity(&m_matWeaponHandTM);
}

cBody::~cBody()
{
	D3DXFrameDestroy(m_pFrameRoot, m_pAlloc);
	//m_pAlloc->DestroyFrame(m_pFrame);
	SAFE_DELETE(m_pAlloc);
	SAFE_RELEASE(m_pMesh);
}

void cBody::Setup(char* FolderName, char* FileName)
{
	std::string folder = (std::string)FolderName;
	std::string file = (std::string)FileName;

	m_pAlloc = new cAllocateHierarchy;

	m_pAlloc->SetFolder(folder);

	m_sPath = folder + std::string("/") + file;

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

void cBody::Update()
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
	GetNeckWorld(m_pFrameRoot, nullptr);

	//머리와 목 로컬TM에 월드 매트릭스 곱한다.
	m_matHairTM = m_matHairTM * m_matWorld;
	m_matNeckTM = m_matNeckTM * m_matWorld;
	m_matTailTM = m_matTailTM * m_matWorld;
	m_matWeaponBackTM = m_matWeaponBackTM * m_matWorld;
	m_matWeaponHandTM = m_matWeaponHandTM * m_matWorld;

	UpdateSkinnedMesh(m_pFrameRoot);
}
void cBody::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->LightEnable(0, true);
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//D3DXMatrixIdentity(&m_pFrame->TransformationMatrix);
	ST_BONE* pBone = (ST_BONE*)m_pFrameRoot;
	//D3DXMatrixScaling(&pBone->matWorldTM, 0.3f, 0.3f, 0.3f);//전체 모델의 크기조절
	RecursiveFrameRender(pBone, &pBone->CombinedTransformationMatrix);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetTexture(0, nullptr);
}
void cBody::RecursiveFrameRender(D3DXFRAME* pFrame, D3DXMATRIX* pParentWorldTM)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	D3DXMATRIX matW;
	D3DXMatrixIdentity(&matW);

	matW = pFrame->TransformationMatrix * (*pParentWorldTM);

	pBone->CombinedTransformationMatrix = matW;

	D3DXMATRIXA16 matWorld;

	matWorld = pBone->CombinedTransformationMatrix * m_matWorld;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//m_pMesh->DrawSubset(0);//렌더
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		//g_pD3DDevice->SetTexture(0, pFrame->pMeshContainer->pMaterials);
		for (size_t i = 0; i < pBoneMesh->dwNumSubset; ++i)
		{
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMaterial[i]);
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
			g_pD3DDevice->SetTexture(0, NULL);

			//월드변환 원래대로
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);
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

void cBody::SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIX* pmatParent)
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

void cBody::SetupBoneMatrixPtrs(D3DXFRAME* pFrame)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.

	// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
	// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
	// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
	// 찾아서 월드매트릭스를 걸어줘라.

	//재귀적으로 모든 프레임에 대해서 실행.
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
		pBoneMesh->matSphereW = pBone->CombinedTransformationMatrix;
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
void cBody::GetNeckWorld(D3DXFRAME* pFrame, D3DXMATRIX* pParentTM)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);
	if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Bip01-Neck"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matNeckTM = pBone->CombinedTransformationMatrix;
	}
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Bip01-Head"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matHairTM = pBone->CombinedTransformationMatrix;
	}
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Bip01-Spine1"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matTailTM = pBone->CombinedTransformationMatrix;
	}
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Weapon_Back"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matWeaponBackTM = pBone->CombinedTransformationMatrix;
	}
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("R_Sword"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matWeaponHandTM = pBone->CombinedTransformationMatrix;
	}


	//-180 180 180
	if (pFrame->pFrameSibling)
	{
		GetNeckWorld(pFrame->pFrameSibling, &pBone->CombinedTransformationMatrix);
	}
	if (pFrame->pFrameFirstChild)
	{
		GetNeckWorld(pFrame->pFrameFirstChild, &pBone->CombinedTransformationMatrix);
	}
}


LPD3DXFRAME& cBody::GetFrameRoot()
{
	return this->m_pFrameRoot;
}

void cBody::SetAnimationIndex(int nIndex)
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

DOUBLE cBody::GetAniTrackPeriod(int nIndex)
{
	DOUBLE fTime = 0.f;
	LPD3DXANIMATIONSET pAnimSet;
	m_pAnimControl->GetAnimationSet(nIndex, &pAnimSet);
	fTime = pAnimSet->GetPeriod();
	SAFE_RELEASE(pAnimSet);
	return fTime;
}