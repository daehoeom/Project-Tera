#include "stdafx.h"
#include "cGameObjectManager.h"

#include "cCollision.h"


cGameObjectManager::cGameObjectManager()
{
}

cGameObjectManager::~cGameObjectManager()
{
	for ( auto& gameObjElem : m_objMap )
	{
		SAFE_DELETE( gameObjElem.second );
	}
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