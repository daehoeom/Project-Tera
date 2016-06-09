#include "stdafx.h"
#include "cGameObjectManager.h"

#include "cCollision.h"

cGameObjectManager::cGameObjectManager()
{
}

cGameObjectManager::~cGameObjectManager()
{
}

void cGameObjectManager::Update()
{
	/*for ( auto& object : m_objMap )
	{
		if ( object.second->IsActive( ))
		{
			object.second->Update( );
		}
	}*/

	for (auto& object : m_objMap)
	{
		object.second->Update();
	}
}