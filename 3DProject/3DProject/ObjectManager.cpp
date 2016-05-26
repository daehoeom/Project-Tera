#include "stdafx.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager( )
{
}

ObjectManager::~ObjectManager( )
{
}

void ObjectManager::AddObject( 
	GameObject* obj )
{
	m_objMap.insert( std::make_pair( obj->GetName( ), obj ));
}

GameObject* ObjectManager::FindObject( const std::string& key )
{
	return m_objMap[key];
}

void ObjectManager::DeleteObject( const std::string& key )
{
	m_objMap.erase( key );
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