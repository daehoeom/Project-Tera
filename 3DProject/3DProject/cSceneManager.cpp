#include "stdafx.h"
#include "cSceneManager.h"

#include "cGameObjectManager.h"
#include "cCollisionManager.h"

cSceneManager::cSceneManager( ) :
	m_currScene( nullptr )
{
}

cSceneManager::~cSceneManager( )
{
	SAFE_DELETE( m_currScene );
}

void cSceneManager::Render( )
{
	if ( m_currScene )
	{
		m_currScene->Render( );
	}
}

void cSceneManager::Update( )
{
	if ( m_currScene )
	{
		m_currScene->Update( );
	}
}
