#pragma once
#include "Singleton.h"
#include "cObject.h"

#define g_pObjectManager cObjectManager::Get()

class cObjectManager :
	public TSingleton<cObjectManager>
{
private:
	std::set<cObject*> m_setObject;

public:
	cObjectManager();
	~cObjectManager();

	void AddObject(cObject* pObject)
	{
		m_setObject.insert(pObject);
	}
	void RemoveObject(cObject* pObject)
	{
		m_setObject.erase(pObject);
	}
};

