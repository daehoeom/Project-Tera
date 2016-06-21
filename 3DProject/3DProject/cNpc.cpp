#include "stdafx.h"
#include "cNpc.h"
#include "cBoundingSphere.h"
#include "cNpcSkinnedMesh.h"

cNpc::cNpc()
	: m_fAngle(0.f)
	, m_vPos(0.f, 0.f, 0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocalHair);
	D3DXMatrixIdentity(&m_matLocalHead);
	D3DXMatrixIdentity(&m_matLocal);
	this->SetObjectType(ObjectType::eNpc);

}


cNpc::~cNpc()
{
	for (size_t i = 0; i < m_vecSkinnedMesh.size(); i++)
	{
		SAFE_DELETE(m_vecSkinnedMesh[i]);
	}
}

void cNpc::Setup(char* szFolder, char* szFile)
{
	std::string body = (std::string)szFile;
	body = body + std::string("_Body.X");

	cNpcSkinnedMesh* pBody = new cNpcSkinnedMesh(szFolder, (char*)body.c_str());
	m_vecSkinnedMesh.push_back(pBody);

	std::string head = (std::string)szFile;
	head = head + std::string("_Head.X");

	cNpcSkinnedMesh* pHead = new cNpcSkinnedMesh(szFolder, (char*)head.c_str());
	m_vecSkinnedMesh.push_back(pHead);

	std::string hair = (std::string)szFile;
	hair = hair + std::string("_Hair.X");

	cNpcSkinnedMesh* pHair = new cNpcSkinnedMesh(szFolder, (char*)hair.c_str());
	m_vecSkinnedMesh.push_back(pHair);

	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));
}

void cNpc::Update()
{
	__super::Update(); 

	D3DXMatrixTranslation(&m_matWorld, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMATRIXA16 matLocal, matHair, matHead;
	D3DXMatrixTranslation(&matLocal, 0, 20, 0);
	matLocal = matLocal * m_matWorld;
	this->GetColliderRepo()[0]->SetWorld(&matLocal);

	matLocal = m_matLocal * m_matWorld;

	m_vecSkinnedMesh[0]->SetWorld(&matLocal);

	matHead = m_vecSkinnedMesh[0]->GetNeckTM() * m_matLocalHead;
	matHair = m_vecSkinnedMesh[1]->GetHairTM() * m_matLocalHair;

	m_vecSkinnedMesh[1]->SetLocal(&matHead);

	m_vecSkinnedMesh[2]->SetLocal(&matHair);
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