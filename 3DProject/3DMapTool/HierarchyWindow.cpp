#include "stdafx.h"
#include "HierarchyWindow.h"

#include "resource.h"
#include "cGameObjectManager.h"
#include "InspectorWindow.h"


HWND g_hierarchyWndHandle;

HierarchyWindow::HierarchyWindow( HWND parentWndHandle ) :
	AbstractWindow( 
		L"Hierarchy",
		NULL,
		WS_CAPTION,
		parentWndHandle,
		this->MakeWindowClass( ),
		0,
		0,
		HierarchyWindowWidth,
		HierarchyWindowHeight ),
	m_layer( 0 ),
	m_currSelectedItem( -1 )
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
			
			SetWindowPos( wndHandle, NULL, ownerX-HierarchyWindowWidth,
				ownerY, 0, 0, SWP_NOSIZE );

			this->SetupList( wndHandle );
		}
		break;

	case WM_NOTIFY:
		{
			LPNMHDR lpHdr;
			LPNMLISTVIEW lpListView;

			lpHdr = reinterpret_cast<LPNMHDR>( lParam );
			lpListView = reinterpret_cast<LPNMLISTVIEW>( lParam );

			if ( lpHdr->hwndFrom != m_listHandle )
				break;
			
			switch ( lpHdr->code )
			{
			case NM_CLICK:
				{
					wchar_t findObjName[256] {0};
					ListView_GetItemText( m_listHandle,
						lpListView->iItem, 0,
						findObjName, 256
					);

					if ( findObjName[0] == '\0' )
					{
						break;
					}

					auto object = cGameObjectManager::Get( )->FindObject(
						findObjName
					);
					if ( object )
					{
						auto inspectorWindow = static_cast<InspectorWindow*>(
							this->GetOwner( )->GetChildByName( 
								L"Inspector" ));
							
						inspectorWindow->SetPositionData( object->GetPosition( ) );
						inspectorWindow->SetRotationData( object->GetAngle( ) );
						inspectorWindow->SetScaleData( object->GetScale( ));
					}
				}
				break;
			}
		}
		break;

	/*case WM_SIZE:
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
		break;*/

	case WM_CLOSE:
		return 0;

	case WM_NCLBUTTONDOWN:
		return 0;
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

void HierarchyWindow::GetSelectedItemText( 
	wchar_t* outText, int32_t maxCount ) const
{
	ListView_GetItemText( m_listHandle,
		this->GetSelectedItemIndex( ),
		0,
		outText,
		maxCount );
}

int32_t HierarchyWindow::GetSelectedItemIndex( ) const
{
	int32_t index = ListView_GetNextItem( m_listHandle,
		-1, LVNI_ALL | LVNI_SELECTED );

	return index;
}

void HierarchyWindow::AddListItem( 
	const std::wstring& itemName )
{
	LVITEMW lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = m_layer;
	lvItem.iSubItem = 0;
	lvItem.pszText = const_cast<wchar_t*>( itemName.c_str( ));
	ListView_InsertItem( m_listHandle, &lvItem );

	++m_layer;
}

void HierarchyWindow::SetupList( HWND wndHandle )
{
	RECT rt;
	GetClientRect( wndHandle, &rt );

	m_listHandle = CreateWindowEx( 
		NULL, 
		WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LVS_REPORT | LVS_SINGLESEL, -1, -1, rt.right+2, rt.bottom+2,
		wndHandle,
		NULL, GetModuleHandle( 0 ), NULL 
	);

	LVCOLUMN lvCol {0};
	lvCol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = rt.right;
	lvCol.pszText = L"Name";
	lvCol.iSubItem = 0;
	ListView_InsertColumn( m_listHandle, 0, &lvCol );
}
