#include "stdafx.h"
#include "cMainGame.h"
#include "cGrid.h"
#include "cPlayer.h"
#include "cBoundingBox.h"
#include "cCollisionManager.h"
#include "cGameObjectManager.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cNpcManager.h"
#include "cGiantStone.h"

cPlayer* g_player = nullptr;

cMainGame::cMainGame( )
	: m_pGrid(nullptr)
	, m_pLoader(nullptr)
	, m_pNpc(nullptr)
	, m_pMonster(nullptr)
{
	SetupManagers();

	/*SOUNDMANAGER->addSound("¹è°æÀ½", "./BGM/War_Start_00.ogg");
	SOUNDMANAGER->play("¹è°æÀ½", 1.f);*/

	m_pGrid = new cGrid;
	g_player = new cPlayer;

	//m_pMonster = new cGiantStone;

	/*D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	m_pLoader = new cObjLoader;
	m_pLoader->Load("./Map/Height.obj", m_vecGroup, &mat);*/
}

cMainGame::~cMainGame()
{
	SAFE_DELETE( m_pGrid );
	SAFE_DELETE( g_player);
	SAFE_DELETE( m_pLoader );
	SAFE_DELETE( m_pNpc );
	SAFE_DELETE(m_pMonster);

	for each(auto p in m_vecGroup)
	{
		SAFE_RELEASE(p);
	}

	g_pTextureManager->Destroy();
}

void cMainGame::Update()
{
	cCamera::Get()->Update(&g_player->GetPosition());
	cCollisionManager::Get( )->Update( );

	if (g_player)
	{
		g_player->Update();
	}

	if (m_pNpc)
	{
		m_pNpc->Update();
	}

	if (m_pMonster)
	{
		m_pMonster->Update();
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

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//Height¸Ê ·»´õ
	/*for each(auto p in m_vecGroup)
	{
		p->Render();
	}*/

	//±×¸®µå ·»´õ
	if (m_pGrid)
	{
		m_pGrid->Render();
	}

	//ÇÃ·¹ÀÌ¾î ·»´õ
	if (g_player)
	{
		g_player->Render();
	}

	//Npc ·»´õ
	if (m_pNpc)
	{
		m_pNpc->Render();
	}

	//¸ó½ºÅÍ ·»´õ
	if (m_pMonster)
	{
		m_pMonster->Render();
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
	cGameObjectManager::Get( );
	cCollisionManager::Get( );
	cSoundManager::Get();
}