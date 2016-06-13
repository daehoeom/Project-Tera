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
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));

	//밑의 코드는 바운딩체크 할 구 위치 잡아주는 거
	this->GetColliderRepo()[0]->SetLocal(&matT);
	D3DXVECTOR3 vPos(GetPosition().x + matT._41, GetPosition().y + matT._42, GetPosition().z + matT._43);
	this->GetColliderRepo()[0]->SetPosition(vPos);

	D3DXMatrixTranslation(&matT, 0, 30, 0);
	this->AddCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 10.f));
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

	if (GetEnemyState() == ENEMY_DEATH)
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y - 0.23f, GetPosition().z));
		m_fDeathTime = m_pBody->GetAniTrackPeriod(ENEMY_DEATH) - 1.7f;
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