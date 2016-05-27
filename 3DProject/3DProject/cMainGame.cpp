#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cSkinnedMesh.h"

cMainGame::cMainGame() 
	: m_pGrid(NULL)
	, m_pMesh(NULL)
{
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pMesh = new cSkinnedMesh("./¿¤¸°/", "¿¤¸°_¸ö_°ø°Ý.X");
	m_pMesh->SetRandomTrackPosition();
	m_pMesh->SetPosition(D3DXVECTOR3(0, 0, 0));
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pMesh);
}

void cMainGame::Update()
{
	Camera::Get()->Update(NULL);

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

	if (m_pMesh)
	{
		m_pMesh->UpdateAndRender();
	}

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Camera::Get()->WndProc(hWnd, message, wParam, lParam);
}