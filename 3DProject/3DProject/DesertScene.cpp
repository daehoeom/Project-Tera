#include "stdafx.h"
#include "DesertScene.h"
#include "cEnemy.h"

#include "cLightObject.h"
#include "DesertScenePlane.h"
#include "cSkyBox.h"
#include "cEnemyManager.h"
#include "cSprite.h"

namespace
{
	void AdditionalWork( DesertScenePlane** param )
	{
		*param = new DesertScenePlane( "Desert_plane0" );
	}
}

DesertScene::DesertScene( ) :
	m_plane( nullptr ),
	m_loadThread( ReadXML, "Scene/Desert_scene.xml", &m_loadSuccess,
		std::function<void( )>( std::bind( AdditionalWork, &m_plane ))),
	m_loadSuccess( 0 ),
	m_loadingSprite( new cSprite( "CH/LoadingImage/LoadingImage1.bmp" ))
{
	cGameObjectManager::Get( )->AddObject( "SkyBox", new cSkyBox(1) );
	cGameObjectManager::Get()->AddObject("Monster", new cEnemyManager);
}

DesertScene::~DesertScene( )
{
	m_loadThread.join( );
	SAFE_DELETE( m_loadingSprite );
}

void DesertScene::Update( )
{
	if ( !m_loadSuccess )
	{
		if ( m_loadingSprite )
		{
			m_loadingSprite->Update( );
		}
		return;
	}

	if ( m_plane )
	{
		m_plane->Update( );
	}

	if ( g_player )
	{
		g_player->Update( );
	}
}

void DesertScene::Render( )
{
	if ( !m_loadSuccess )
	{
		if ( m_loadingSprite )
		{
			m_loadingSprite->Render( );
		}
		return;
	}

	if ( m_plane )
	{
		m_plane->Render( );
	}

	//플레이어 렌더
	if ( g_player )
	{
		g_player->Render( );
	}
}
