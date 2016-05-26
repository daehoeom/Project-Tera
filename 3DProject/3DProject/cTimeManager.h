#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
	SINGLETONE(cTimeManager);

private:
	DWORD m_dwLastUpdateTime;
	DWORD m_dwDeltaTime;

public:
	void Update();
	float GetDeltaTime();
};
