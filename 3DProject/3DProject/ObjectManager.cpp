#include "stdafx.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager( )
{
}

ObjectManager::~ObjectManager( )
{
}

void ObjectManager::Update( float fElapsedTime )
{
	for ( auto& object : m_objMap )
	{
		if ( object.second->IsActive( ))
		{
			object.second->Update( fElapsedTime );
		}
	}
}