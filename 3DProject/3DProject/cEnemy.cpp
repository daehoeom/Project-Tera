#include "stdafx.h"
#include "cEnemy.h"


cEnemy::cEnemy()
	:cCollisionObject("monster")
	, m_pBody(nullptr)
	, m_nMaxHp(1000)
	, m_nCurrentHp(1000)
{
}


cEnemy::~cEnemy()
{
}

void cEnemy::Update()
{
}

void cEnemy::Render()
{

}