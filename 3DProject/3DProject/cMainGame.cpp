#include "stdafx.h"
#include "cMainGame.h"

#include "cGrid.h"
#include "cSkinnedMesh.h"
#include "cPlayer.h"


cMainGame::cMainGame( )
{
	this->SetupManagers( );

	m_player.reset( new cPlayer );
	
	m_grid.reset( new cGrid );

	m_enemy.reset( new cSkinnedMesh("./LongTusk/", "LongTusk_Idle.X" ));
	//m_enemy->SetRandomTrackPosition();
}

cMainGame::~cMainGame()
{
}

void cMainGame::Update()
{
	cCamera::Get()->Update(NULL);
	
	if ( m_player )
		m_player->Update( );

	g_pTimeManager->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	if ( m_grid )
		m_grid->Render( );
	if ( m_player )
		m_player->Render( );
	if( m_enemy )
		m_enemy->UpdateAndRender();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	cCamera::Get()->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::SetupManagers( )
{
	/*
		WARNING! & TODO:
		All of managers ( e.g. singleton object ) 
		must be initialized from here.
	*/

	cDeviceManager::Get( );
	// Must be called after cDeviceManager initialized
	cCamera::Get( );
	cSkinnedMeshManager::Get( );
	cTextureManager::Get( );
	// Etc
	cRandomUtil::Setup();
	cTimeManager::Get( );
	cKeyManager::Get( );
	cObjectManager::Get( );
}
