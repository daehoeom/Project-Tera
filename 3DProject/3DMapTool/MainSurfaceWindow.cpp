#include "stdafx.h"
#include "MainSurfaceWindow.h"

#include "resource.h"
#include "cDeviceManager.h"


HWND g_mainWndHandle;

MainSurfaceWindow::MainSurfaceWindow( ) :
	AbstractWindow( 
		L"3DMapTool",
		WS_EX_ACCEPTFILES,
		WS_OVERLAPPEDWINDOW,
		this->MakeWindowClass( ),
		GetSystemMetrics( SM_CXSCREEN )/2-(MainWindowWidth/2),
		GetSystemMetrics( SM_CYSCREEN )/2-(MainWindowHeight/2),
		MainWindowWidth,
		MainWindowHeight
	),
	m_dropQueryPath( new wchar_t[MAX_PATH] )
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

LRESULT MainSurfaceWindow::MessageProc( 
	HWND wndHandle, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam )
{
	switch ( msg )
	{
	case WM_CREATE:
		int n = 3;
		break;

	case WM_DROPFILES:
		{
			DragQueryFileW(( HDROP )wParam, 0, 
				m_dropQueryPath.get(), MAX_PATH );
			
			static int32_t hierarchyObjIndex = 0;
		}
		break;

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

	case WM_MOVE:
		{
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
	/*g_pD3DDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 0,0,255 ), 1.f, 0.f );

	g_pD3DDevice->BeginScene( );
	g_pD3DDevice->EndScene( );

	g_pD3DDevice->Present( nullptr, nullptr, nullptr, nullptr );*/
}

void MainSurfaceWindow::OnMove( 
	AbstractWindow* sender, 
	int x, 
	int y )
{
	sender->Move( x, y );
}

void MainSurfaceWindow::OnSize( 
	AbstractWindow* sender, 
	int width, 
	int height )
{
}

WNDCLASSEXW MainSurfaceWindow::MakeWindowClass( )
{
	WNDCLASSEXW wcex {0};
	HINSTANCE instanceHandle = GetModuleHandle( nullptr );

	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = nullptr; // Ignore, using member function
	wcex.hInstance = instanceHandle;
	wcex.hIcon = LoadIcon( g_instHandle, MAKEINTRESOURCE( IDI_MY3DMAPTOOL ));
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = (HBRUSH)( COLOR_WINDOW+1 );
	wcex.lpszMenuName = MAKEINTRESOURCEW( IDC_MY3DMAPTOOL );
	wcex.lpszClassName = L"MainSurfaceWindowClass";
	wcex.hIconSm = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ));

	return wcex;
}