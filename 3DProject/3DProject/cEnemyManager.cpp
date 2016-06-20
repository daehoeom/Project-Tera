#include "stdafx.h"
#include "cEnemyManager.h"
#include "cArgoniteFemaleMagician.h"
#include "cArgoniteKallashGuardLeader.h"
#include "cMadmadDuo.h"
#include "cPixie.h"
#include "cEnemy.h"

cEnemyManager::cEnemyManager()
{
	cEnemy* enemy = new cArgoniteFemaleMagician;
	m_vecEnemy.push_back(enemy);
}


cEnemyManager::~cEnemyManager()
{
	for (size_t i = 0; i < m_vecEnemy.size(); i++)
	{
		SAFE_DELETE(m_vecEnemy[i]);
	}
}

void cEnemyManager::Update()
{
	for (size_t i = 0; i < m_vecEnemy.size(); i++)
	{
		m_vecEnemy[i]->Update();
	}
}

void cEnemyManager::Render()
{
	for (size_t i = 0; i < m_vecEnemy.size(); i++)
	{
		m_vecEnemy[i]->Render();
	}
}