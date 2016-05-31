#include "stdafx.h"
#include "cObjectManager.h"

#include "cCollision.h"

cObjectManager::cObjectManager( )
{
}

cObjectManager::~cObjectManager( )
{
}

void cObjectManager::UpdateCollisionState( )
{
	for ( auto& elemOp1 : m_objMap )
	{
		// elemOp1 Has no collider?
		if ( !elemOp1.second->GetCollider( ))
		{
			continue;
		}

		for ( auto& elemOp2 : m_objMap )
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

void cObjectManager::Update( )
{
	for ( auto& object : m_objMap )
	{
		if ( object.second->IsActive( ))
		{
			object.second->Update( );
		}
	}
}