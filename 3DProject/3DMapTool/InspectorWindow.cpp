#include "stdafx.h"
#include "InspectorWindow.h"

#include "resource.h"


//HWND g_hierarchyWndHandle;
//
//
//InspectorWindow::InspectorWindow( ) :
//	AbstractWindow( INSPECTORWINDOW_TITLENAME )
//{
//}
//
//InspectorWindow::~InspectorWindow( )
//{
//}
//
//LRESULT InspectorWindow::MsgProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam )
//{
//	InspectorWindow* extraMemAsWindow = reinterpret_cast<InspectorWindow*>(
//		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ) );
//
//	if ( extraMemAsWindow && 
//		extraMemAsWindow->m_wndDelegate )
//	{
//		switch ( msg )
//		{
//		case WM_CREATE:
//			{
//			}
//			break;
//
//		case WM_SIZE:
//			extraMemAsWindow->m_wndDelegate->OnSize( 
//				extraMemAsWindow, LOWORD( lParam ), HIWORD( lParam ));
//			break;
//
//		case WM_NCLBUTTONDOWN:
//			return 0;
//		}
//	}
//
//	if ( msg == WM_DESTROY )
//	{
//		PostQuitMessage( 0 );
//	}
//
//	return DefWindowProc( wndHandle, msg, wParam, lParam );
//}
//
//void InspectorWindow::OnIdle( )
//{
//}
//
//void InspectorWindow::SetDelegate( 
//	IWindowDelegate * windowDelegate )
//{
//	m_wndDelegate = windowDelegate;
//}
//
//HWND InspectorWindow::SetupWindowComponents( )
//{
//	this->SetupWindowClass( );
//	HWND myWindowHandle = this->SetupWindow( );
//	this->SetupList( );
//
//	return myWindowHandle;
//}
//
//void InspectorWindow::SetupWindowClass( )
//{
//	WNDCLASSEXW wcex{ 0 };
//	
//	wcex.cbSize =			sizeof( WNDCLASSEX );
//	wcex.style =			CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc =		InspectorWindow::MsgProc;
//	wcex.hInstance =		g_instHandle;
//	wcex.hIcon =			LoadIcon( g_instHandle, MAKEINTRESOURCE( IDI_MY3DMAPTOOL ) );
//	wcex.hCursor =			LoadCursor( nullptr, IDC_ARROW );
//	wcex.hbrBackground =	(HBRUSH)( COLOR_WINDOW+1 );
//	wcex.lpszClassName =	this->GetClassName( ).c_str() ;
//	wcex.hIconSm =			LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );
//	
//	RegisterClassExW( &wcex );
//}
//
//HWND InspectorWindow::SetupWindow( )
//{
//	int ownerX, ownerY, ownerWidth, ownerHeight;
//	GetOwner( )->GetPosition( &ownerX, &ownerY );
//	GetOwner( )->GetSize( &ownerWidth, &ownerHeight );
//
//	g_hierarchyWndHandle = CreateWindowExW(
//		NULL,
//		this->GetClassName( ).c_str( ),
//		this->GetName( ).c_str( ), 
//		WS_BORDER,
//		ownerX+ownerWidth,
//		ownerY,
//		InspectorWindowWidth,
//		InspectorWindowHeight,
//		nullptr, 
//		nullptr, 
//		GetModuleHandle( nullptr ), 
//		nullptr 
//	);
//	
//
//	SetWindowLongPtrW(
//		g_hierarchyWndHandle,
//		GWLP_USERDATA, // Save window ptr to window-personal storage
//		reinterpret_cast<LONG_PTR>( this )
//	);
//
//	ShowWindow( g_hierarchyWndHandle, SW_SHOW );
//	UpdateWindow( g_hierarchyWndHandle );
//
//
//	return g_hierarchyWndHandle;
//}
//
//void InspectorWindow::SetupList( )
//{
//	InitCommonControls( );
//
//	RECT rt;
//	GetClientRect( g_hierarchyWndHandle, &rt );
//
//	m_listHandle = CreateWindowEx( 
//		NULL, 
//		WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
//		LVS_REPORT | LVS_SHOWSELALWAYS, 0, 0, rt.right, rt.bottom, g_hierarchyWndHandle, 
//		NULL, GetModuleHandle( 0 ), NULL 
//	);
//	//SetWindowTheme( m_listHandle, L"explorer", NULL );
//
//
//	m_lvCol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
//	m_lvCol.fmt = LVCFMT_LEFT;
//	m_lvCol.cx = rt.right;
//	m_lvCol.pszText = L"Name";
//	m_lvCol.iSubItem = 0;
//	ListView_InsertColumn( m_listHandle, 0, &m_lvCol );
//
//
//}
