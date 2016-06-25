#include "stdafx.h"
#include "cMainGame.h"
#include "cCollisionManager.h"
#include "cSceneManager.h"
#include "cShaderManager.h"
#include "TestScene.h"
#include "DesertScene.h"

cPlayer* g_player = nullptr;
cLightObject* g_lightObject = nullptr;

cMainGame::cMainGame( )
	: m_pFont(NULL)
	, m_fFrameTime(0.f)
	, m_dwFrameCount(0)
	, m_dwFrameRate(0)
{
	SetupManagers();

	g_player = new cPlayer;
	g_lightObject = new cLightObject;
	cCamera::Get( )->SetFollowingTarget( g_player );
	
	cSceneManager::Get( )->LoadScene<DesertScene>( );

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	fd.Height = 25;
	fd.Width = 12;
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, "MD¾Æ·ÕÃ¼");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

cMainGame::~cMainGame( )
{
	SAFE_RELEASE(m_pFont);
	SAFE_DELETE( g_player );
	SAFE_DELETE( g_lightObject );
}

void cMainGame::Update( )
{
	m_fFrameTime += g_pTimeManager->GetDeltaTime();

	m_dwFrameCount++;

	if (m_fFrameTime > 1.f)
	{
		m_dwFrameRate = m_dwFrameCount;
		m_fFrameTime = 0.f;
		m_dwFrameCount = 0;
	}

	cCamera::Get( )->Update( );
	
	cSceneManager::Get( )->Update( );
	cGameObjectManager::Get( )->Update( );
	cCollisionManager::Get( )->Update( );
	
	g_pTimeManager->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255),
		1.0f, 0
	);
	
	g_pD3DDevice->BeginScene();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	cGameObjectManager::Get( )->Render( );
	cSceneManager::Get( )->Render( );
	
	g_pD3DDevice->EndScene();

	RECT rc;
	SetRect(&rc, 10, 10, 40, 20);

	char str[128];
	sprintf_s(str, "%d", m_dwFrameRate);
	m_pFont->DrawTextA(NULL,
		str,
		strlen(str),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255));

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
	cShaderManager::Get( );
	cCamera::Get( );
	// Etc
	cRandomUtil::Setup();
	cTimeManager::Get( );
	cKeyManager::Get( );
	cCollisionManager::Get( );
	cGameObjectManager::Get( );
	cSoundManager::Get();
	cSceneManager::Get();
}