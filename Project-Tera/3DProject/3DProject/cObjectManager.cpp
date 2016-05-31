#include "stdafx.h"
#include "cObjectManager.h"

#include "cCollision.h"

cObjectManager::cObjectManager( )
{
}

cObjectManager::~cObjectManager( )
{
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