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


TestScene::TestScene( )
{
	this->ReadXML( "./CH/SCENE.xml" );
	
	//cGameObjectManager::Get( )->AddObject(
	//	"Monster1", new cArgoniteKallashGuardLeader 
	//);

	//auto* monster2 = cGameObjectManager::Get( )->AddObject( 
	//	"Monster2", new cArgoniteKallashGuardLeader 
	//);
	//monster2->SetPosition({ 0.f, 0.f, -150.f });

	cGameObjectManager::Get( )->AddObject( "SkyBox", new cSkyBox );
	cGameObjectManager::Get( )->AddObject( "Grid", new cGrid );

	m_plane = new TestScenePlane( "Plane0" );

	/*D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	m_pLoader = new cObjLoader;
	m_pLoader->Load("./Map/Height.obj", m_vecGroup, &mat);*/

}

TestScene::~TestScene( )
{
	SAFE_DELETE( m_plane );
}

void TestScene::Render( )
{
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
	if ( KEYMANAGER->isOnceKeyDown( VK_SPACE ) )
	{
		cGameObjectManager::Get( )->ResetAllObject( );
		cSceneManager::Get( )->LoadScene( new DesertScene );
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