#include "stdafx.h"
#include "cCollisionManager.h"

#include "cCollisionObject.h"


cCollisionManager::cCollisionManager( )
{
}

cCollisionManager::~cCollisionManager( )
{
}

void cCollisionManager::Update( )
{
	for ( auto& elemOp1 : m_collisionMap )
	{
		// elemOp1 Has no collider?
		if ( !elemOp1.second->GetCollider( ))
		{
			continue;
		}

		for ( auto& elemOp2 : m_collisionMap )
		{
			// Compare target is same as elemOp1?
			// Or elemOp2 has no collider? 
			if ( elemOp1 == elemOp2 ||
				!elemOp2.second->GetCollider( ))
			{
				continue;
			}

			// Then, elemOp1 and elemOp2 is different with,
			// And both have colliders.

		}
			
	}
}

void cCollisionManager::AddObject(
	cCollisionObject* target )
{
	const uintptr_t key =
		reinterpret_cast<uintptr_t>( target );

	auto iter = m_collisionMap.find( key );
	if ( iter == m_collisionMap.end( ) )
	{
		m_collisionMap[key] = target;
	}
}

void cCollisionManager::EraseObject( 
	cCollisionObject* target )
{
	const uintptr_t key =
		reinterpret_cast<uintptr_t>( target );
	m_collisionMap.erase( key );
}
