#include "stdafx.h"
#include "MainSurfaceWindow.h"

#include "resource.h"


HWND g_mainWndHandle;


MainSurfaceWindow::MainSurfaceWindow( ) :
	AbstractWindow( MAINWINDOW_TITLENAME )
{
}

MainSurfaceWindow::~MainSurfaceWindow( )
{
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

LRESULT MainSurfaceWindow::MsgProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// 메뉴 선택을 구문 분석합니다.
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(g_instHandle, MAKEINTRESOURCE(IDD_ABOUTBOX), wndHandle, About);
				break;
			case IDM_EXIT:
				DestroyWindow( wndHandle );
				break;
			}
		}
        break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}

	return DefWindowProc( wndHandle, msg, wParam, lParam );
}

void MainSurfaceWindow::OnIdle( )
{
}

HWND MainSurfaceWindow::SetupWindowComponents( )
{
	this->SetupWindowClass( );

	HWND myWindowHandle = this->SetupWindow( );
	return myWindowHandle;
}

void MainSurfaceWindow::SetupWindowClass( )
{
	WNDCLASSEXW wcex{ 0 };
	
	wcex.cbSize =			sizeof( WNDCLASSEX );
	wcex.style =			CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc =		MainSurfaceWindow::MsgProc;
	wcex.hInstance =		g_instHandle;
	wcex.hIcon =			LoadIcon( g_instHandle, MAKEINTRESOURCE( IDI_MY3DMAPTOOL ) );
	wcex.hCursor =			LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground =	(HBRUSH)( COLOR_WINDOW+1 );
	wcex.lpszMenuName =		MAKEINTRESOURCEW( IDC_MY3DMAPTOOL );
	wcex.lpszClassName =	this->GetClassName( ).c_str() ;
	wcex.hIconSm =			LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );
	
	RegisterClassExW( &wcex );
}

HWND MainSurfaceWindow::SetupWindow( )
{
	g_mainWndHandle = CreateWindowW(
		this->GetClassName( ).c_str( ),
		this->GetName( ).c_str( ), 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		0, 
		CW_USEDEFAULT, 
		0, 
		nullptr, 
		nullptr, 
		GetModuleHandle( nullptr ), 
		nullptr 
	);

	ShowWindow( g_mainWndHandle, SW_SHOW );
	UpdateWindow( g_mainWndHandle );

	return g_mainWndHandle;
}

void MainSurfaceWindow::InitD3DSurface( )
{
}
