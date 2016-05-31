// 3DMapTool.cpp : 응용 프로그램에 대한 진입점을 정의합니다.

#include "stdafx.h"
#include "3DMapTool.h"

#include "MainSurfaceWindow.h"


HINSTANCE g_instHandle;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	g_instHandle = hInstance;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DMAPTOOL));

	std::unique_ptr<MainSurfaceWindow> mainSurfaceWnd( 
		new MainSurfaceWindow );
	mainSurfaceWnd->Setup( );

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
		}
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
