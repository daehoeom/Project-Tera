#pragma once
#include <mutex>
#include "Singleton.h"

class cCollisionManager :
	public TSingleton<cCollisionManager>
{
	using _CollisonMapTy = std::map<uintptr_t, cCollisionObject*>;
	using iterator = _CollisonMapTy::iterator;

public:
	void Update( );
	void SetAutoUpdate( bool isAutoUpdate );

	void AddObject( cCollisionObject* target );
	void EraseObject( cCollisionObject* target );
	void ClearAllObject( );

	iterator begin( );
	iterator end( );

protected:
	cCollisionManager( );
	virtual ~cCollisionManager( );

private:
	std::mutex m_mutex;
	bool m_isAutoUpdatable;
	_CollisonMapTy m_collisionMap;
};

inline cCollisionManager::iterator cCollisionManager::begin( )
{ 
	return m_collisionMap.begin( ); 
}

inline cCollisionManager::iterator cCollisionManager::end( )
{ 
	return m_collisionMap.end( ); 
}

inline void cCollisionManager::SetAutoUpdate( bool isAutoUpdate )
{
	m_isAutoUpdatable = isAutoUpdate;
}