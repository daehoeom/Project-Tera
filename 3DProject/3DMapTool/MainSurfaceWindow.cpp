#include "stdafx.h"
#include "MainSurfaceWindow.h"

#include "resource.h"
#include "cDeviceManager.h"

HWND g_mainWndHandle;


MainSurfaceWindow::MainSurfaceWindow( ) :
	AbstractWindow( MAINWINDOW_TITLENAME ),
	m_dropQueryPath( new wchar_t[MAX_PATH] )
{
}

MainSurfaceWindow::~MainSurfaceWindow( )
{
	delete m_dropQueryPath;
	m_dropQueryPath = nullptr;
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
	MainSurfaceWindow* extraMemAsWindow = reinterpret_cast<MainSurfaceWindow*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ) );

	if ( extraMemAsWindow )
	{
		switch ( msg )
		{
		case WM_DROPFILES:
			{
				DragQueryFileW(( HDROP )wParam, 0, 
					extraMemAsWindow->m_dropQueryPath, MAX_PATH );
			
				static int32_t hierarchyObjIndex = 0;
			}
			break;

		case WM_CREATE:
			{
				RECT rt;
				GetWindowRect( wndHandle, &rt );
				extraMemAsWindow->m_prevPos = 
					{ rt.left, rt.top };
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
				RECT rt;
				GetWindowRect( wndHandle, &rt );
				
				int moveX = rt.left - extraMemAsWindow->m_prevPos.x;
				int moveY = rt.top - extraMemAsWindow->m_prevPos.y;

				for ( auto* elem : extraMemAsWindow->GetChildRepo( ) )
				{
					elem->Move( moveX, moveY );
				}

				extraMemAsWindow->m_prevPos = 
					{ rt.left, rt.top };
			}
			break;

		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		}
	}

	return DefWindowProc( wndHandle, msg, wParam, lParam );
}

void MainSurfaceWindow::OnIdle( )
{
	g_pD3DDevice->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 0,0,255 ), 1.f, 0.f );

	g_pD3DDevice->BeginScene( );
	g_pD3DDevice->EndScene( );

	g_pD3DDevice->Present( nullptr, nullptr, nullptr, nullptr );
}

void MainSurfaceWindow::OnMove( 
	AbstractWindow* sender, int x, int y )
{
	sender->Move( x, y );
}

void MainSurfaceWindow::OnSize( AbstractWindow * sender, int width, int height )
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
	const int halfScreenWidth = GetSystemMetrics( SM_CXSCREEN )/2;
	const int halfScreenHeight = GetSystemMetrics( SM_CYSCREEN )/2;

	g_mainWndHandle = CreateWindowExW(
		WS_EX_ACCEPTFILES,
		this->GetClassName( ).c_str( ),
		this->GetName( ).c_str( ), 
		WS_OVERLAPPEDWINDOW,
		halfScreenWidth-(MainWindowWidth/2),
		halfScreenHeight-(MainWindowHeight/2),
		MainWindowWidth,
		MainWindowHeight,
		nullptr, 
		nullptr, 
		GetModuleHandle( nullptr ), 
		nullptr 
	);

	SetWindowLongPtrW(
		g_mainWndHandle,
		GWLP_USERDATA, // Save window ptr to window-personal storage
		reinterpret_cast<LONG_PTR>( this )
	);

	ShowWindow( g_mainWndHandle, SW_SHOW );
	UpdateWindow( g_mainWndHandle );

	cDeviceManager::Get( )->Setup( g_mainWndHandle );

	return g_mainWndHandle;
}
