#include "stdafx.h"
#include "cSceneManager.h"

SceneManager::SceneManager( ) :
	m_currScene( nullptr )
{
}

SceneManager::~SceneManager( )
{
	SAFE_DELETE( m_currScene );
}

void SceneManager::LoadScene( IScene * newScene )
{
	SAFE_DELETE( m_currScene );
	m_currScene = newScene;
}

void SceneManager::Render( )
{
	if ( m_currScene )
	{
		m_currScene->Render( );
	}
}

void SceneManager::Update( )
{
	if ( m_currScene )
	{
		m_currScene->Update( );
	}
}
