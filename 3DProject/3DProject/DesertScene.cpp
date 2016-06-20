#include "stdafx.h"
#include "DesertScene.h"

#include "cLightObject.h"
#include "DesertScenePlane.h"
#include "cSkyBox.h"

DesertScene::DesertScene( ) :
	m_plane( nullptr )
{
	this->ReadXML( "./CH/Desert_scene.xml" );
	
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
	m_plane = new DesertScenePlane( "Desert_plane0" );

	/*D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	m_pLoader = new cObjLoader;
	m_pLoader->Load("./Map/Height.obj", m_vecGroup, &mat);*/
}

DesertScene::~DesertScene( )
{
}

void DesertScene::Update( )
{
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
	if ( m_plane )
	{
		m_plane->Render( );
	}

	//ÇÃ·¹ÀÌ¾î ·»´õ
	if ( g_player )
	{
		g_player->Render( );
	}
}
