#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cSkyBox.h"

cMainGame::cMainGame() 
	: m_pGrid(NULL)
	, m_pSkyBox(NULL)
{
	cRandomUtil::Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	if (m_pSkyBox == nullptr)
	{
		m_pSkyBox = new cSkyBox;
		m_pSkyBox->Setup();
	}
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pSkyBox);
}

void cMainGame::Update()
{
	Camera::Get()->Update(NULL);


	if (m_pSkyBox)
	{
		m_pSkyBox->Update();
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

	if (m_pSkyBox)
	{
		m_pSkyBox->Render();
	}

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Camera::Get()->WndProc(hWnd, message, wParam, lParam);
}