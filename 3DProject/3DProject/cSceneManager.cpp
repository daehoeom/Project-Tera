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

void cSceneManager::LoadScene( IScene * newScene )
{
	if ( m_currScene )
	{
		delete m_currScene;
		m_currScene = nullptr;
	}

	m_currScene = newScene;
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
