#pragma once
#include "Singleton.h"

class cCollisionObject;
class cCollisionManager :
	public TSingleton<cCollisionManager>
{
	using _CollisonMapTy = std::map<uintptr_t, cCollisionObject*>;

public:
	void Update( );
	
	void AddObject( cCollisionObject* target );
	void EraseObject( cCollisionObject* target );

protected:
	cCollisionManager( );
	virtual ~cCollisionManager( );

private:
	_CollisonMapTy m_collisionMap;
};

