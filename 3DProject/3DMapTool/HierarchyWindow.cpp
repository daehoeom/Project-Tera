#include "stdafx.h"
#include "HierarchyWindow.h"

#include "resource.h"

HWND g_hierarchyWndHandle;

HierarchyWindow::HierarchyWindow( ) :
	AbstractWindow( 
		L"Hierarchy",
		NULL,
		WS_CAPTION,
		this->MakeWindowClass( ),
		0,
		0,
		HierarchyWindowWidth,
		HierarchyWindowHeight )
{
}

HierarchyWindow::~HierarchyWindow( )
{
}

LRESULT HierarchyWindow::MessageProc( 
	HWND wndHandle, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam )
{
	switch ( msg )
	{
	case WM_CREATE:
		{
			int ownerX, ownerY, ownerWidth, ownerHeight;
			this->GetOwner( )->GetPosition( &ownerX, &ownerY );
			this->GetOwner( )->GetSize( &ownerWidth, &ownerHeight );
			
			SetWindowPos( wndHandle, NULL, ownerX+ownerWidth, 
				ownerY, 0, 0, SWP_NOSIZE );

			SetWindowPos( wndHandle, NULL, 0, 
				0, HierarchyWindowWidth, HierarchyWindowHeight, SWP_NOMOVE );
		
			this->SetupList( wndHandle );
		}
		break;

	case WM_SIZE:
		if ( m_wndDelegate )
		{
			m_wndDelegate->OnSize( 
				this, LOWORD( lParam ), HIWORD( lParam ));
		}
		break;

	case WM_MOVE:
		if ( m_wndDelegate )
		{
			m_wndDelegate->OnMove( 
				this, LOWORD( lParam ), HIWORD( lParam ));
		}
		break;

	case WM_NCLBUTTONDOWN:
		return 0;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}

	return DefWindowProc( wndHandle, msg, wParam, lParam );
}

WNDCLASSEXW HierarchyWindow::MakeWindowClass( )
{
	WNDCLASSEXW wcex {0};
	HINSTANCE instanceHandle( GetModuleHandle( nullptr ));
	
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = nullptr;
	wcex.hInstance = instanceHandle;
	wcex.hIcon = LoadIcon( instanceHandle, MAKEINTRESOURCE( IDI_MY3DMAPTOOL ) );
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW+1 );
	wcex.lpszClassName = L"HierarchyWindowClass";
	wcex.hIconSm = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );
	
	return wcex;
}

void HierarchyWindow::OnIdle( )
{
}

void HierarchyWindow::AddListItem( 
	const wchar_t* itemName )
{
}

//void HierarchyWindow::AddListItem( 
//	const wchar_t * itemName )
//{
//	//wchar_t tempBuf[5];
//	//wsprintf( tempBuf, L"%d", m_Layer );
//
//	m_lvItem.mask = LVIF_TEXT;
//	m_lvItem.iItem = m_Layer;
//	m_lvItem.iSubItem = 0;
//	ListView_InsertItem( m_listHandle, &m_lvItem );
//	ListView_SetItemText( m_listHandle, m_Layer, 0, L"WOWOW" );
//
//	++m_Layer;
//}

void HierarchyWindow::SetupList( HWND wndHandle )
{
	RECT rt;
	GetClientRect( wndHandle, &rt );

	m_listHandle = CreateWindowEx( 
		NULL, 
		WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LVS_REPORT | LVS_SHOWSELALWAYS, 0, 0, rt.right, rt.bottom, 
		wndHandle, 
		NULL, GetModuleHandle( 0 ), NULL 
	);

	m_lvCol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	m_lvCol.fmt = LVCFMT_LEFT;
	m_lvCol.cx = rt.right;
	m_lvCol.pszText = L"Name";
	m_lvCol.iSubItem = 0;
	ListView_InsertColumn( m_listHandle, 0, &m_lvCol );
}
