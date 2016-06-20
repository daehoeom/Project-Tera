#include "stdafx.h"
#include "DesertScene.h"

#include "cSkyBox.h"
#include "cSprite.h"
#include "cLightObject.h"
#include "DesertScenePlane.h"


namespace
{
	void AdditionalWork( DesertScenePlane** param )
	{
		*param = new DesertScenePlane( "Desert_plane0" );
	}
}

DesertScene::DesertScene( ) :
	m_plane( nullptr ),
	m_loadThread( ReadXML, "./CH/Desert_scene.xml", &m_loadSuccess,
		std::function<void( )>( std::bind( AdditionalWork, &m_plane ))),
	m_loadSuccess( 0 ),
	m_loadingSprite( new cSprite( "C:/Users/ggomdyu/Desktop/documents-export-2016-06-20/LoadingImage63_Tex.tga" ))
{
	//cGameObjectManager::Get( )->AddObject(
	//	"Monster1", new cArgoniteKallashGuardLeader 
	//);

	//auto* monster2 = cGameObjectManager::Get( )->AddObject( 
	//	"Monster2", new cArgoniteKallashGuardLeader 
	//);
	//monster2->SetPosition({ 0.f, 0.f, -150.f });

	cGameObjectManager::Get( )->AddObject( "SkyBox", new cSkyBox(1) );
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
	if ( m_plane )
	{
		m_plane->Update( );
	}

	if ( m_loadingSprite )
	{
		m_loadingSprite->Update( );
	}

	if ( g_player )
	{
		g_player->Update( );
	}
}

void DesertScene::Render( )
{
	if ( m_plane )
	{
		m_plane->Render( );
	}

	if ( m_loadingSprite )
	{
		m_loadingSprite->Render( );
	}

	//플레이어 렌더
	if ( g_player )
	{
		g_player->Render( );
	}
}
