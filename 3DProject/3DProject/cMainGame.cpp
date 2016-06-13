#include "stdafx.h"
#include "cMainGame.h"

#include "cCollisionManager.h"
#include "cSceneManager.h"
#include "TestScene.h"

cPlayer* g_player = nullptr;

cMainGame::cMainGame( )
{
	SetupManagers();

	g_player = new cPlayer;

	/*SOUNDMANAGER->addSound("배경음", "./BGM/War_Start_00.ogg");
	SOUNDMANAGER->play("배경음", 1.f);*/
	cSceneManager::Get( )->LoadScene( 
		new TestScene( "./Scene.xml" ));
}

cMainGame::~cMainGame( )
{
	g_pTextureManager->Destroy( );
}

void cMainGame::Update( )
{
	cCamera::Get( )->Update( &g_player->GetPosition( ));

	cSceneManager::Get( )->Update( );
	cCollisionManager::Get( )->Update( );

	g_pTimeManager->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0
	);

	g_pD3DDevice->BeginScene();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	cSceneManager::Get( )->Render( );

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	cCamera::Get()->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::SetupManagers( )
{
	cDeviceManager::Get( );
	// Must be called after cDeviceManager initialized
	cTextureManager::Get( );
	cCamera::Get( );
	// Etc
	cRandomUtil::Setup();
	cTimeManager::Get( );
	cKeyManager::Get( );
	cGameObjectManager::Get( );
	cCollisionManager::Get( );
	cSoundManager::Get();
	cSceneManager::Get();
}