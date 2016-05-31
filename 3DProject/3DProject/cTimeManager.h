#pragma once
#include "Singleton.h"

#define g_pTimeManager cTimeManager::Get()

class cTimeManager :
	public TSingleton<cTimeManager>
{
private:
	DWORD m_dwLastUpdateTime;
	DWORD m_dwDeltaTime;

protected:
	cTimeManager( );
	virtual ~cTimeManager( );

public:
	void Update();
	float GetDeltaTime();
};
