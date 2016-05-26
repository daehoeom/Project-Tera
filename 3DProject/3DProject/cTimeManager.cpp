#include "StdAfx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager(void)
{
	m_dwLastUpdateTime = GetTickCount();
}


cTimeManager::~cTimeManager(void)
{
}

void cTimeManager::Update()
{
	DWORD dwCurrUpdateTime = GetTickCount();
	m_dwDeltaTime = dwCurrUpdateTime - m_dwLastUpdateTime;
	m_dwLastUpdateTime = dwCurrUpdateTime;
}

float cTimeManager::GetDeltaTime()
{
	return (float)m_dwDeltaTime / 1000.f;
}
