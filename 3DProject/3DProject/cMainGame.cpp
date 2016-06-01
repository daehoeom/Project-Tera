#include "stdafx.h"
#include "cMainGame.h"
#include "cGrid.h"
#include "cPlayer.h"
#include "cBoundingBox.h"
#include "cCollisionManager.h"
#include "cObjectManager.h"


cMainGame::cMainGame( )
	: m_pGrid(NULL)

{
	m_pGrid = new cGrid;
	m_player = new cPlayer;

	/*for ( int i = 0; i < 50; i++ )
	{
		cB* box( new cB );
		box->SetPosition( {(float)(rand()%100), 0.f, (float)(rand()%100) });
		b.push_back( box );
	}*/
}

cMainGame::~cMainGame()
{
	SAFE_DELETE( m_pGrid );
	SAFE_DELETE( m_player );

	for ( auto& elem : b )
	{
		SAFE_DELETE( elem );
	}

	g_pTextureManager->Destroy();
}

void cMainGame::Update()
{
	cCamera::Get()->Update(NULL);
	cCollisionManager::Get( )->Update( );

	/*for ( auto& elem : b )
		elem->Update( );*/


	if (m_player)
	{
		m_player->Update();
	}

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

	
	/*for ( auto& elem : b )
		elem->Render( );*/

	if (m_pGrid)
	{
		m_pGrid->Render();
	}

	if (m_player)
	{
		m_player->Render();
	}

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
	cObjectManager::Get( );
	cCollisionManager::Get( );
}