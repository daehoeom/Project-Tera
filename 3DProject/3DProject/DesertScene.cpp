#include "stdafx.h"
#include "DesertScene.h"
#include "cEnemy.h"
#include "cLightObject.h"
#include "DesertScenePlane.h"
#include "cSkyBox.h"
#include "cArgoniteKallashGuardLeader.h"
#include "cGiantStone.h"
#include "cMadmadDuo.h"
#include "cArgoniteFemaleMagician.h"
#include "cPixie.h"
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
	m_monsterRepo.push_back(new cPixie);
	m_monsterRepo[0]->SetPosition({ 100, 300, 100 });
	m_monsterRepo[0]->SetEnemyOrigin(&m_monsterRepo[0]->GetPosition());

	cGameObjectManager::Get( )->AddObject( "SkyBox", new cSkyBox( 1 ));
}

DesertScene::~DesertScene( )
{
	m_loadThread.join( );
	SAFE_DELETE( m_loadingSprite );

	for ( auto enemyElem : m_monsterRepo )
	{
		SAFE_DELETE( enemyElem );
	}
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
		g_player->SetPosition({
			g_player->GetPosition( ).x,
			m_plane->GetHeight( g_player ),
			g_player->GetPosition( ).z
		});
	}

	for ( auto enemyElem : m_monsterRepo )
	{
		enemyElem->Update( );

		//몬스터가 죽기 전까지는 Height맵 높이 값에 따라 Y축이 변동
		if (enemyElem->GetEnemyState() != ENEMY_DEATH)
		{
			enemyElem->SetPosition({ enemyElem->GetPosition().x, m_plane->GetHeight(enemyElem),
				enemyElem->GetPosition().z });
		}
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

	for ( auto enemyElem : m_monsterRepo )
	{
		enemyElem->Render( );
	}
}
