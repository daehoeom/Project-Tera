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
	SOUNDMANAGER->addSound("전투맵", "./Music/BGM(사막).ogg", true, true);
	
	SOUNDMANAGER->addSound("ArgoniteFemaleMagician공격", "./Music/ArgoniteFemaleMagician(Attack).ogg", false, false);
	SOUNDMANAGER->addSound("ArgoniteFemaleMagician죽음", "./Music/ArgoniteFemaleMagician(Death).ogg", false, false);
	
	SOUNDMANAGER->addSound("ArgoniteKallashGuardLeader공격", "./Music/ArgoniteKallashGuardLeader(Attack).ogg", false, false);
	SOUNDMANAGER->addSound("ArgoniteKallashGuardLeader죽음", "./Music/ArgoniteKallashGuardLeader(Death).ogg", false, false);

	SOUNDMANAGER->addSound("Pixie공격", "./Music/Pixie(Attack).ogg", false, false);
	SOUNDMANAGER->addSound("Pixie죽음", "./Music/Pixie(Death).ogg", false, false);

	SOUNDMANAGER->addSound("Madmad공격", "./Music/Madman(Attack).ogg", false, false);
	SOUNDMANAGER->addSound("Madmad죽음", "./Music/Madman(Death).ogg", false, false);

	SOUNDMANAGER->play("전투맵", 1.f);

	m_monsterRepo.push_back(new cMadmadDuo);
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

	SOUNDMANAGER->stop("전투맵");
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
