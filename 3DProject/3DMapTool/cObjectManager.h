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
	void Destroy()
	{
		assert(m_setObject.empty() && "생성된 cObject를 상속받은 객체 중 해제되지 않은 객체가 있습니다.");
	}
};

