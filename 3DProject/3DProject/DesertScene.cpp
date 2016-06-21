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
	//cGameObjectManager::Get( )->AddObject(
	//	"Monster1", new cArgoniteKallashGuardLeader 
	//);

	//auto* monster2 = cGameObjectManager::Get( )->AddObject( 
	//	"Monster2", new cArgoniteKallashGuardLeader 
	//);
	//monster2->SetPosition({ 0.f, 0.f, -150.f });

	cGameObjectManager::Get( )->AddObject( "SkyBox", new cSkyBox(1) );
	cGameObjectManager::Get()->AddObject("Monster", new cEnemyManager);
	//cGameObjectManager::Get( )->AddObject( "Grid", new cGrid );
	//

	/*D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	m_pLoader = new cObjLoader;
	m_pLoader->Load("./Map/Height.obj", m_vecGroup, &mat);*/
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
