#include "stdafx.h"
#include "cNpc.h"
#include "cBoundingSphere.h"
#include "cSkinnedMesh.h"

cNpc::cNpc()
	: m_fAngle(0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocalHair);
	D3DXMatrixIdentity(&m_matLocalHead);

	this->SetObjectType(ObjectType::eNpc);

}


cNpc::~cNpc()
{
	
}

void cNpc::Setup(char* szFolder, char* szFile)
{
	//몸파일 등록
	//m_pBody = new cBody;

	//std::string body = (std::string)szFile;
	//body = body + std::string("_Body.X");

	//m_pBody->Setup(szFolder, (char*)body.c_str());

	//m_pBody->SetWorld(&m_matWorld);

	////헤어파일 등록
	//m_pHair = new cHair;
	//std::string hair = (std::string)szFile;
	//hair = hair + std::string("_Hair.X");

	//m_pHair->SetHairTM(&m_pBody->GetHairTM());
	//m_pHair->Setup(szFolder, (char*)hair.c_str());

	////얼굴파일 등록
	//m_pFace = new cFace;
	//std::string face = (std::string)szFile;
	//face = face + std::string("_Head.X");

	//m_pFace->SetNeckTM(&m_pBody->GetNeckTM());
	//m_pFace->Setup(szFolder, (char*)face.c_str());

	std::string body = (std::string)szFile;
	body = body + std::string("_Body.X");

	cSkinnedMesh* pBody = new cSkinnedMesh(szFolder, (char*)body.c_str());
	pBody->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_vecSkinnedMesh.push_back(pBody);

	std::string head = (std::string)szFile;
	head = head + std::string("_Head.X");

	cSkinnedMesh* pHead = new cSkinnedMesh(szFolder, (char*)head.c_str());
	pHead->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_vecSkinnedMesh.push_back(pHead);

	std::string hair = (std::string)szFile;
	hair = hair + std::string("_Hair.X");

	cSkinnedMesh* pHair = new cSkinnedMesh(szFolder, (char*)hair.c_str());
	pHair->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_vecSkinnedMesh.push_back(pHair);

	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));
}

void cNpc::Update()
{
	__super::Update(); 

	m_vecSkinnedMesh[0]->SetPosition(this->GetPosition());


	D3DXMATRIXA16 matLocal;
	D3DXMatrixTranslation(&matLocal, 0, 20, 0);
	matLocal = matLocal * m_matWorld;
	this->GetColliderRepo()[0]->SetWorld(&matLocal);
}

void cNpc::Render()
{
	__super::Render();

	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++)
	{
		m_vecSkinnedMesh[i]->UpdateAndRender();
	}
	
	this->GetColliderRepo()[0]->Render();
}