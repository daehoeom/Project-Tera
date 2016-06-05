// 3DMapTool.cpp : 응용 프로그램에 대한 진입점을 정의합니다.

#include "stdafx.h"
#include "3DMapTool.h"
#include <crtdbg.h>

#include "MainSurfaceWindow.h"
#include "HierarchyWindow.h"
#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cObjectManager.h"
#include "cGameObjectManager.h"
#include "cCamera.h"
#include "DirectInput.h"
#include "LightObject.h"
#include "InspectorWindow.h"

#pragma comment( linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"" )

std::unique_ptr<MainSurfaceWindow> g_mainSurfaceWnd;
std::unique_ptr<InspectorWindow> g_inspectorWnd;
std::unique_ptr<HierarchyWindow> g_hierarchyWnd;

HINSTANCE g_instHandle;

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#define new new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif


	g_instHandle = hInstance;

	InitCommonControls( );
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DMAPTOOL));

	g_mainSurfaceWnd.reset( new MainSurfaceWindow );
	g_mainSurfaceWnd->SetupWindowComponents( );
	
	g_hierarchyWnd.reset( new HierarchyWindow( g_mainSurfaceWnd->GetWindowHandle( )));
	g_mainSurfaceWnd->AddChild( g_hierarchyWnd.get( ));
	g_hierarchyWnd->SetOwner( g_mainSurfaceWnd.get( ));
	g_hierarchyWnd->SetDelegate( g_mainSurfaceWnd.get( ));
	g_hierarchyWnd->SetupWindowComponents( );

	g_inspectorWnd.reset( new InspectorWindow( g_mainSurfaceWnd->GetWindowHandle( )));
	g_mainSurfaceWnd->AddChild( g_inspectorWnd.get( ));
	g_inspectorWnd->SetOwner( g_mainSurfaceWnd.get( ));
	g_inspectorWnd->SetDelegate( g_mainSurfaceWnd.get( ));
	g_inspectorWnd->SetupWindowComponents( );


	// Init managers
	cDeviceManager::Get( )->Setup( g_mainSurfaceWnd->GetWindowHandle( ));
	cTextureManager::Get( );
	cObjectManager::Get( );
	cGameObjectManager::Get( );
	cDirectInput::Get( )->Setup( g_mainSurfaceWnd->GetWindowHandle( ));
	cCameraObject* camera = new cCameraObject( 
		g_mainSurfaceWnd->GetWindowHandle( ), L"Camera" );
	g_hierarchyWnd->AddListItem( camera->GetName( ));
	LightObject* obj = new LightObject( L"Light" );
	g_hierarchyWnd->AddListItem( obj->GetName( ));


    MSG msg {0};
    while ( true )
    {
		// Message does exist
		if ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ))
		{
			if ( msg.message != WM_QUIT )
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				break;
			}
		}
		else
		{
			cDirectInput::Get( )->Update( );
			g_mainSurfaceWnd->OnIdle( );
		}
    }

    return (int) msg.wParam;
}

