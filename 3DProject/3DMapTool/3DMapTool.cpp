// 3DMapTool.cpp : 응용 프로그램에 대한 진입점을 정의합니다.

#include "stdafx.h"
#include "3DMapTool.h"

#include "MainSurfaceWindow.h"
#include "HierarchyWindow.h"
#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cObjectManager.h"
#include "cGameObjectManager.h"
#include "cCamera.h"

#pragma comment( linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"" )


HINSTANCE g_instHandle;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	g_instHandle = hInstance;

	InitCommonControls( );
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DMAPTOOL));

	std::unique_ptr<MainSurfaceWindow> mainSurfaceWnd( new MainSurfaceWindow );
	mainSurfaceWnd->SetupWindowComponents( );

	std::unique_ptr<HierarchyWindow> hierarchyWnd(
		new HierarchyWindow( mainSurfaceWnd->GetWindowHandle( )));

	mainSurfaceWnd->SetChild( hierarchyWnd.get( ));
	hierarchyWnd->SetOwner( mainSurfaceWnd.get( ));
	hierarchyWnd->SetDelegate( mainSurfaceWnd.get( ));
	hierarchyWnd->SetupWindowComponents( );

	cDeviceManager::Get( )->Setup( mainSurfaceWnd->GetWindowHandle( ));
	cCamera::Get( )->Setup( mainSurfaceWnd->GetWindowHandle( ));
	cTextureManager::Get( );
	cObjectManager::Get( );
	cGameObjectManager::Get( );

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
			// Idle
			mainSurfaceWnd->OnIdle( );
			hierarchyWnd->OnIdle( );
		}
    }

    return (int) msg.wParam;
}

