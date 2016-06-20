#include "stdafx.h"
#include "TestScene.h"
#include "cPlayer.h"
#include "cBoundingBox.h"
#include "cGameObjectManager.h"
#include "cGroup.h"
#include "cNpcManager.h"
#include "cSkyBox.h"
#include "cArgoniteKallashGuardLeader.h"
#include "cGrid.h"
#include "TestScenePlane.h"
#include "cLightObject.h"
#include "cKeyManager.h"
#include "DesertScene.h"
#include "cSceneManager.h"
#include "Console.h"
#include "cSprite.h"

namespace
{
	void AdditionalWork( TestScenePlane** param )
	{
		*param = new TestScenePlane( "Plane0" );
	}
}

TestScene::TestScene( ) :
	m_plane( nullptr ),
	m_loadThread( ReadXML, "./CH/SCENE.xml", &m_loadSuccess,
		std::function<void( )>( std::bind( AdditionalWork, &m_plane )) ),
	m_loadSuccess( 0 ),
	m_loadingSprite( new cSprite( "CH/LoadingImage/LoadingImage63_Tex.tga" ))
{
	//cGameObjectManager::Get( )->AddObject(
	//	"Monster1", new cArgoniteKallashGuardLeader 
	//);

	//auto* monster2 = cGameObjectManager::Get( )->AddObject( 
	//	"Monster2", new cArgoniteKallashGuardLeader 
	//);
	//monster2->SetPosition({ 0.f, 0.f, -150.f });

	cGameObjectManager::Get( )->AddObject( "SkyBox", new cSkyBox(0) );
	cGameObjectManager::Get( )->AddObject( "Grid", new cGrid );
	cGameObjectManager::Get()->AddObject("Npc", new cNpcManager);

	//loadThread.join( );


	/*D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	m_pLoader = new cObjLoader;
	m_pLoader->Load("./Map/Height.obj", m_vecGroup, &mat);*/

}

TestScene::~TestScene( )
{
	m_loadThread.join( );

	SAFE_DELETE( m_plane );
	SAFE_DELETE( m_loadingSprite );
}

void TestScene::Render( )
{
	if ( !m_loadSuccess )
	{
		Log( "로딩을_알리는_메시지" );
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
	if (g_player)
	{
		g_player->Render();
	}
}

void TestScene::Update( )
{
	if ( !m_loadSuccess )
	{
		return;
	}

	if ( KEYMANAGER->isOnceKeyDown( VK_SPACE ) )
	{
		cSceneManager::Get( )->LoadScene<DesertScene>( );
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