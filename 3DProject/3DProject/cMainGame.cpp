#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cSkinnedMesh.h"
#include "cParticle_Firework.h"

cMainGame::cMainGame() 
	: m_pGrid(NULL)
	, m_pFire(NULL)
{
	cRandomUtil::Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	if (m_pFire == nullptr)
	{
		m_pFire = new cParticle_Firework(D3DXVECTOR3(-15, 20, 100), 6000);
		m_pFire->Setup("fireworks_flare.bmp");
	}
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pFire);
}

void cMainGame::Update()
{
	Camera::Get()->Update(NULL);

	if (m_pFire)
	{
		m_pFire->Update();
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

	if (m_pGrid)
	{
		m_pGrid->Render();
	}

	if (m_pFire)
	{
		m_pFire->Render();
	}

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Camera::Get()->WndProc(hWnd, message, wParam, lParam);
}