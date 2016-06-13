#pragma once
#include "Singleton.h"

class cCollisionManager :
	public TSingleton<cCollisionManager>
{
	using _CollisonMapTy = std::map<uintptr_t, cCollisionObject*>;
	using iterator = _CollisonMapTy::iterator;

public:
	void Update( );

	void AddObject( cCollisionObject* target );
	void EraseObject( cCollisionObject* target );

	iterator begin( );
	iterator end( );

protected:
	cCollisionManager( );
	virtual ~cCollisionManager( );

private:
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