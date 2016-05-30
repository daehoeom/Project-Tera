#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cSkinnedMesh.h"
#include "cParticle_Firework.h"
#include "cSkyBox.h"

cMainGame::cMainGame() 
	: m_pGrid(NULL)
	, m_pFire(NULL)
	, m_pBody(NULL)
	, m_pHead(NULL)
	, m_pSkyBox(NULL)
{
	cRandomUtil::Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	if (m_pFire == nullptr)
	{
		m_pFire = new cParticle_Firework(D3DXVECTOR3(-15, 20, 100), 6000);
		m_pFire->Setup("fireworks_flare.bmp");
	}

	if (m_pBody == nullptr)
	{
		m_pBody = new cSkinnedMesh("./¿¤¸°/", "¿¤¸°_¸ö_°ø°Ý.X");
		m_pBody->SetPosition(D3DXVECTOR3(0, 0, 0));
		m_pBody->SetRandomTrackPosition();
	}

	if (m_pHead == nullptr)
	{
		m_pHead = new cSkinnedMesh("./¿¤¸°/", "¿¤¸°_¾ó±¼_°ø°Ý.X");
		m_pHead->SetPosition(D3DXVECTOR3(0, 0, 0));
		m_pHead->SetRandomTrackPosition();
	}
	
	if (m_pSkyBox == nullptr)
	{
		m_pSkyBox = new cSkyBox;
		m_pSkyBox->Setup();
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

	//if (m_pFire)
	//{
	//	m_pFire->Update();
	//}

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

	/*if (m_pFire)
	{
		m_pFire->Render();
	}*/

	m_pBody->UpdateAndRender();

	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.f);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matR);
	m_pHead->UpdateAndRender();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Camera::Get()->WndProc(hWnd, message, wParam, lParam);
}