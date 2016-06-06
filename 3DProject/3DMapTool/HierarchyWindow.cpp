#include "stdafx.h"
#include "HierarchyWindow.h"

#include "resource.h"
#include "cGameObject.h"
#include "cGameObjectManager.h"
#include "cCamera.h"
#include "InspectorWindow.h"


HierarchyWindow::HierarchyWindow( HWND parentWndHandle ) :
	AbstractWindow( 
		L"Hierarchy", NULL, WS_CAPTION,
		parentWndHandle, this->MakeWindowClass( ),
		0, 0, HierarchyWindowWidth, HierarchyWindowHeight 
	),
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
			
			this->SetPosition( ownerX-HierarchyWindowWidth, ownerY );
			this->SetupListView( wndHandle );
		}
		break;

	case WM_NOTIFY:
		{
			LPNMHDR lpHdr = reinterpret_cast<LPNMHDR>( lParam );
			LPNMLISTVIEW lpListView = reinterpret_cast<LPNMLISTVIEW>( lParam );

			if ( lpHdr->hwndFrom == m_listHandle )
			{
				switch ( lpHdr->code )
				{
				case NM_DBLCLK:
					this->OnItemDoubleClicked( lpListView );
					break;

				case LVN_ITEMCHANGED:
					this->OnItemClicked( lpListView );
					break;
				}
			}
		}
		break;

	// Ignore moving & Ctrl+F4
	case WM_CLOSE:
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

void HierarchyWindow::OnItemDoubleClicked( 
	LPNMLISTVIEW lpListView )
{
	auto* object = this->GetSelectedItemAsObject( );
	if ( object )
	{
		// Move Camera

		auto* camera = cGameObjectManager::Get( )->FindObject(
			L"Camera" );

		const D3DXVECTOR3& cameraRot = camera->GetAngle( );
		D3DXVECTOR3 cameraDir( 0, 0, 1 );
		D3DXMATRIXA16 matRot, matRotX, matRotY;
		D3DXMatrixRotationX( &matRotX, cameraRot.x );
		D3DXMatrixRotationY( &matRotY, cameraRot.y );
		matRot = matRotX*matRotY;
		D3DXVec3TransformNormal( &cameraDir, &cameraDir, &matRot );

		camera->SetPosition( {
			object->GetPosition( ).x,
			object->GetPosition( ).y,
			object->GetPosition( ).z
		} );
		camera->Move( cameraDir*-20 );
	}
}

void HierarchyWindow::OnItemClicked( 
	LPNMLISTVIEW lpListView )
{
	auto* object = this->GetSelectedItemAsObject( );
	if ( object )
	{
		g_inspectorWnd->SetPositionData( object->GetPosition( ));
		g_inspectorWnd->SetRotationData( object->GetAngle( ));
		g_inspectorWnd->SetScaleData( object->GetScale( ));
	}
}

cGameObject* HierarchyWindow::GetSelectedItemAsObject( )
{
	wchar_t findObjName[256]{ 0 };
	ListView_GetItemText( m_listHandle,
		this->GetSelectedItemIndex( ), 0,
		findObjName, 256
	);

	if ( findObjName[0] == '\0' )
	{
		return nullptr;
	}

	return cGameObjectManager::Get( )->FindObject( findObjName );
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

void HierarchyWindow::SetupListView( HWND wndHandle )
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
