#include "stdafx.h"
#include "cNpcManager.h"
#include "cNpc.h"
#include "cBoundingSphere.h"

cNpcManager::cNpcManager()
{
	cNpc* m_pNpc = nullptr;
	D3DXMATRIXA16 world;

	//상점Npc
	m_pNpc = new cNpc;
	m_pNpc->Setup("./CH/NpcCastanic/", "NpcCastanic");
	m_pNpc->SetPos(D3DXVECTOR3(200.f, 0.f, -100.f));
	m_pNpc->SetType(eNpcType::NPC_SHOP);
	m_vecNpc.push_back(m_pNpc);

	//퀘스트Npc
	m_pNpc = new cNpc;
	m_pNpc->Setup("./CH/NpcFemaleElf/", "NpcFemaleElf");
	m_pNpc->SetPos(D3DXVECTOR3(-50.f, 0.f, 200.f));
	m_pNpc->SetType(eNpcType::NPC_QUEST);
	m_vecNpc.push_back(m_pNpc);

	//대장간Npc
	 m_pNpc = new cNpc;
	m_pNpc->Setup("./CH/NpcPopori/", "NpcPopori");
	D3DXMATRIX matT;
	m_pNpc->SetPos(D3DXVECTOR3(600, 0, 0));
	D3DXMatrixTranslation(&matT, -1.5f, -7.f, 0.f);
	m_pNpc->SetLocalHead(&(D3DXMATRIXA16)matT);
	D3DXMatrixTranslation(&matT, -2.5f, -10.f, 0.f);
	m_pNpc->SetLocalHair(&(D3DXMATRIXA16)matT);
	m_pNpc->SetType(eNpcType::NPC_BLACKSMITH);
	m_vecNpc.push_back(m_pNpc);
}

cNpcManager::~cNpcManager()
{
	for (size_t i = 0; i < m_vecNpc.size(); i++)
	{
		SAFE_DELETE(m_vecNpc[i]);
	}
}

void cNpcManager::Update()
{
	for (size_t i = 0; i < m_vecNpc.size(); i++)
	{
		m_vecNpc[i]->Update();
	}
}

void cNpcManager::Render()
{
	for (size_t i = 0; i < m_vecNpc.size(); i++)
	{
		m_vecNpc[i]->Render();
	}
}