#include "stdafx.h"
#include "cArgoniteFemaleMagician.h"
#include "cEnemySkinMesh.h"

cArgoniteFemaleMagician::cArgoniteFemaleMagician()
{
	m_pBody = new cEnemySkinMesh;
	m_pBody->Setup("./CH/ArgoniteFemaleMagician", "ArgoniteFemaleMagician.X");

	D3DXMATRIX matR;
	D3DXMatrixRotationY(&matR, D3DX_PI / 2.f);
	m_pBody->SetLocal(&matR);

	//무조건 몬스터 생성시 포지션 잡아줘야댐

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 50, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));

	//밑의 코드는 바운딩체크 할 구 위치 잡아주는 거
	this->GetColliderRepo()[0]->SetLocal(&matT);
	D3DXVECTOR3 vPos(GetPosition().x + matT._41, GetPosition().y + matT._42, GetPosition().z + matT._43);
	this->GetColliderRepo()[0]->SetPosition(vPos);

	D3DXMatrixTranslation(&matT, 0, 30, 0);
	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));
	this->GetColliderRepo()[1]->SetLocal(&matT);
	vPos = D3DXVECTOR3(GetPosition().x + matT._41, GetPosition().y + matT._42, GetPosition().z + matT._43);
	this->GetColliderRepo()[1]->SetPosition(vPos);
}


cArgoniteFemaleMagician::~cArgoniteFemaleMagician()
{
	SAFE_DELETE(m_pBody);
}

void cArgoniteFemaleMagician::Update()
{
	__super::Update();

	for (size_t i = 0; i < this->GetColliderRepo().size(); i++)
	{
		this->GetColliderRepo()[i]->SetWorld(&m_matWorld);
		D3DXMATRIXA16 mat = this->GetColliderRepo()[i]->GetLocal() * this->GetColliderRepo()[i]->GetWorld();
		D3DXVECTOR3 vPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
		this->GetColliderRepo()[i]->SetPosition(vPos);
	}

	if (GetEnemyState() == ENEMY_DEATH)
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y - 0.23f, GetPosition().z));

		//이동량만큼 월드매트릭스 수정
		D3DXMatrixTranslation(&m_matWorld, GetPosition().x, GetPosition().y, GetPosition().z); 
	}
}

void cArgoniteFemaleMagician::Render()
{
	__super::Render();

	if (m_pBody)
	{
		m_pBody->Render();
	}
}