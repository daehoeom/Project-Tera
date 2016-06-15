#include "stdafx.h"
#include "cGameObjectManager.h"

#include "cCollision.h"


cGameObjectManager::cGameObjectManager()
{
}

cGameObjectManager::~cGameObjectManager()
{
	this->ResetAllObject( );
}

void cGameObjectManager::Update()
{
	for ( auto& object : m_objMap )
	{
		//if ( object.second->IsActive( ))
		//{
			object.second->Update( );
		//}
	}
}

void cGameObjectManager::Render( )
{
	for ( auto& object : m_objMap )
	{
		//if ( object.second->IsActive( ))
		//{
			object.second->Render( );
		//}
	}
}

void cGameObjectManager::ResetAllObject( )
{
	for ( auto& objElem : m_objMap )
	{
		SAFE_DELETE( objElem.second );
	}

	m_objMap.clear( );
}