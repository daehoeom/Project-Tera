#include "stdafx.h"
#include "cSceneManager.h"

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
	SAFE_DELETE( m_currScene );
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
