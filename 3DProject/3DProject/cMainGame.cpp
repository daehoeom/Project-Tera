#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cSkinnedMesh.h"
#include "cParticle_Firework.h"


cMainGame::cMainGame( )
	: m_pGrid(NULL)
	, m_pFire(NULL)
	, m_pEneny(NULL)
{

	/*
		WARNING! & TODO:
		All of managers ( e.g. singleton object ) 
		must be initialized from here.
	*/

	cRandomUtil::Setup();
	cDeviceManager::Get( );
	cTimeManager::Get( );
	cCamera::Get( );
	cSkinnedMeshManager::Get( );
	cKeyManager::Get( );
	cObjectManager::Get( );


	m_pGrid = new cGrid;
	
	if (m_pFire == nullptr)
	{
		m_pFire = new cParticle_Firework(D3DXVECTOR3(-15, 20, 100), 6000);
		m_pFire->Setup("fireworks_flare.bmp");
	}


	if (m_pEneny == nullptr)
	{
		m_pEneny = new cSkinnedMesh("./LongTusk/", "LongTusk_Idle.X");
		m_pEneny->SetPosition(D3DXVECTOR3(0, 0, 0));
		m_pEneny->SetRandomTrackPosition();
	}
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pFire);
	SAFE_DELETE(m_pEneny);
}

void cMainGame::Update()
{
	cCamera::Get()->Update(NULL);

	m_player.Update( );

	//boundingBox1.Update( NULL);

	//if (m_pFire)
	//{
	//	m_pFire->Update();
	//}

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


	if (m_pGrid)
	{
		m_pGrid->Render();
	}

	m_player.Render( );

	/*if (m_pFire)
	{
		m_pFire->Render();
	}*/

	m_pEneny->UpdateAndRender();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	cCamera::Get()->WndProc(hWnd, message, wParam, lParam);
}