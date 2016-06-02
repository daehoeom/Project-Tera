#include "stdafx.h"
#include "cNpc.h"
#include "cBody.h"
#include "cFace.h"
#include "cHair.h"
#include "cBoundingSphere.h"

cNpc::cNpc()
	: cCollisionObject("npc")
	, m_pBody(nullptr)
	, m_pHair(nullptr)
	, m_pFace(nullptr)
	, m_pBound(nullptr)
	, m_fAngle(0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocalHair);
	D3DXMatrixIdentity(&m_matLocalHead);

}


cNpc::~cNpc()
{
	SAFE_DELETE(m_pBody);
	SAFE_DELETE(m_pHair);
	SAFE_DELETE(m_pFace);
	SAFE_DELETE(m_pBound);
}

void cNpc::Setup(char* szFolder, char* szFile)
{
	//몸파일 등록
	m_pBody = new cBody;

	std::string body = (std::string)szFile;
	body = body + std::string("_Body.X");

	m_pBody->Setup(szFolder, (char*)body.c_str());

	m_pBody->SetWorld(&m_matWorld);

	//헤어파일 등록
	m_pHair = new cHair;
	std::string hair = (std::string)szFile;
	hair = hair + std::string("_Hair.X");

	m_pHair->SetHairTM(&m_pBody->GetHairTM());
	m_pHair->Setup(szFolder, (char*)hair.c_str());

	//얼굴파일 등록
	m_pFace = new cFace;
	std::string face = (std::string)szFile;
	face = face + std::string("_Head.X");

	m_pFace->SetNeckTM(&m_pBody->GetNeckTM());
	m_pFace->Setup(szFolder, (char*)face.c_str());

	m_pBound = new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f);
}

void cNpc::Update()
{
	if (m_pBody)
	{
		m_pBody->Update();
		m_pBody->SetWorld(&m_matWorld);
	}

	if (m_pHair)
	{
		D3DXMATRIXA16 mat;
		mat = m_pBody->GetHairTM() * m_matLocalHair;
		m_pHair->SetHairTM(&mat);
		m_pHair->Update();
	}

	if (m_pFace)
	{
		D3DXMATRIXA16 mat;
		mat = m_pBody->GetNeckTM() * m_matLocalHead;
		m_pFace->SetNeckTM(&mat);
		m_pFace->Update();
	}

	if (m_pBound)
	{
		m_pBound->Update();

		//바운딩 박스 올림
		D3DXMATRIXA16 matLocal;
		D3DXMatrixTranslation(&matLocal, 0, 20, 0);
		matLocal = matLocal * m_matWorld;
		m_pBound->SetWorld(&matLocal);
	}
}

void cNpc::Render()
{
	if (m_pBody)
	{
		m_pBody->Render();
	}

	if (m_pHair)
	{
		m_pHair->Render();
	}

	if (m_pFace)
	{
		m_pFace->Render();
	}

	if (m_pBound)
	{
		m_pBound->Render();
	}

}