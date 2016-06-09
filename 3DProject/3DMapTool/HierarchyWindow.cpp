#include "stdafx.h"
#include "HierarchyWindow.h"

#include "BoundingBox.h"
#include "resource.h"
#include "cGameObject.h"
#include "cGameObjectManager.h"
#include "cCamera.h"
#include "InspectorWindow.h"
#include "IColliseable.h"


HierarchyWindow::HierarchyWindow( HWND parentWndHandle ) :
	AbstractWindow( 
		L"Hierarchy", NULL, WS_CAPTION,
		parentWndHandle, this->MakeWindowClass( ),
		0, 0, HierarchyWindowWidth, HierarchyWindowHeight 
	),
	m_layer( 0 ),
	m_listHandle( nullptr )
{
}

HierarchyWindow::~HierarchyWindow( )
{
}


INT_PTR CALLBACK ColliderMsgProc(
	HWND wndHandle,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam )
{
	switch ( msg )
	{
	case WM_INITDIALOG:
		{
			auto* object = static_cast<IColliseable*>(
				g_hierarchyWnd->GetSelectedItemAsObject( ));
			if ( object )
			{
				auto* boundingBox = static_cast<BoundingBox*>( 
					object->GetCollider( ));

				SetDlgItemText( wndHandle, IDC_MINXPOS, 
					std::to_wstring( boundingBox->GetMin( ).x ).c_str( ));
				SetDlgItemText( wndHandle, IDC_MINYPOS, 
					std::to_wstring( boundingBox->GetMin( ).y ).c_str( ));
				SetDlgItemText( wndHandle, IDC_MINZPOS, 
					std::to_wstring( boundingBox->GetMin( ).z ).c_str( ));

				SetDlgItemText( wndHandle, IDC_MAXXPOS, 
					std::to_wstring( boundingBox->GetMax( ).x ).c_str( ));
				SetDlgItemText( wndHandle, IDC_MAXYPOS, 
					std::to_wstring( boundingBox->GetMax( ).y ).c_str( ));
				SetDlgItemText( wndHandle, IDC_MAXZPOS, 
					std::to_wstring( boundingBox->GetMax( ).z ).c_str( ));
			}
		}
		break;

	case WM_COMMAND:
		switch ( wParam ) 
		{
		case IDAABBOK:
			{
				wchar_t buf[256];
				auto* object = static_cast<IColliseable*>(
					g_hierarchyWnd->GetSelectedItemAsObject( ) 
				);
				
				BoundingBox* boundingBox = static_cast<BoundingBox*>(
						object->GetCollider( ));
				
				D3DXVECTOR3 vMin;
				GetDlgItemText( wndHandle, IDC_MINXPOS, buf, 256 );
				vMin.x = _wtof( buf );
				GetDlgItemText( wndHandle, IDC_MINYPOS, buf, 256 );
				vMin.y = _wtof( buf );
				GetDlgItemText( wndHandle, IDC_MINZPOS, buf, 256 );
				vMin.z = _wtof( buf );

				D3DXVECTOR3 vMax;
				GetDlgItemText( wndHandle, IDC_MAXXPOS, buf, 256 );
				vMax.x = _wtof( buf );
				GetDlgItemText( wndHandle, IDC_MAXYPOS, buf, 256 );
				vMax.y = _wtof( buf );
				GetDlgItemText( wndHandle, IDC_MAXZPOS, buf, 256 );
				vMax.z = _wtof( buf );

				boundingBox->SetMinMax( vMin, vMax );

				EndDialog( wndHandle, IDAABBOK );
			}
			return TRUE;

		case IDAABBCANCEL:
			EndDialog( wndHandle, IDAABBCANCEL );
			return TRUE;
		}
		break;
	}

	return 0;
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

				case NM_RCLICK:
					{
						auto* object = GetSelectedItemAsObject( );

						if ( object &&
							object->GetIdenfier( ) != ObjectIdenfier::kCamera &&
							object->GetIdenfier( ) != ObjectIdenfier::kLight &&
							object->GetIdenfier( ) != ObjectIdenfier::kPickTile )
						{
							DialogBox( GetModuleHandle( nullptr ), 
								MAKEINTRESOURCE( IDD_AABB ), 
								wndHandle, 
								ColliderMsgProc );
						}
					}
					break;

				case LVN_ITEMCHANGED:
					this->OnItemClicked( lpListView );
					break;

				case LVN_KEYDOWN:
					{
						LPNMLVKEYDOWN pnkd = ( LPNMLVKEYDOWN )lParam;
						this->OnItemKeyDown( pnkd->wVKey );
					}
					break;

				case LVN_ENDLABELEDIT:
					{
						LPNMLVDISPINFOW di = reinterpret_cast<LPNMLVDISPINFOW>( lParam );

						if ( di->item.pszText != nullptr ) 
						{
							// From
							wchar_t currSelectedItemText[256] {0};
							this->GetSelectedItemText( currSelectedItemText, 256 );

							// To
							const wchar_t* convToItemText = di->item.pszText;


							cGameObject* currGameObj = cGameObjectManager::Get( )->FindObject( 
								currSelectedItemText );

							if ( currGameObj )
							{
								if ( currGameObj->GetIdenfier( ) == ObjectIdenfier::kCamera ||
									currGameObj->GetIdenfier( ) == ObjectIdenfier::kLight ||
									currGameObj->GetIdenfier( ) == ObjectIdenfier::kPickTile )
								{
									MessageBox( GetFocus( ),
										L"이름 변경이 불가능한 객체입니다.",
										L"WARNING!",
										MB_OK | MB_ICONEXCLAMATION
									);
									return FALSE;
								}

								cGameObjectManager::Get( )->EraseObject( 
									currGameObj->GetName( ));
								currGameObj->SetName( convToItemText );
								
								cGameObjectManager::Get( )->AddObject( 
									currGameObj );
							}

							return TRUE;
						}
					}
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
	if ( !m_listHandle )
	{
		return;
	}

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
	if ( !m_listHandle )
	{
		return;
	}

	auto* object = this->GetSelectedItemAsObject( );
	if ( object )
	{
		g_inspectorWnd->SetPositionData( object->GetPosition( ));
		g_inspectorWnd->SetRotationData( object->GetAngle( ));
		g_inspectorWnd->SetScaleData( object->GetScale( ));
	}
}

void HierarchyWindow::OnItemKeyDown( 
	WORD virtualKey )
{
	if ( !m_listHandle )
	{
		return;
	}

	switch ( virtualKey )
	{
	case VK_DELETE:
		{
			const int32_t selectedItemIndex =
				this->GetSelectedItemIndex( );

			// Selected something
			if ( selectedItemIndex != -1 )
			{
				wchar_t selectedObjName[256] {0};
				this->GetSelectedItemText( selectedObjName, 256 );

				auto* findObj = cGameObjectManager::Get( )->FindObject( selectedObjName );
				if ( findObj )
				{
					if ( findObj->GetIdenfier( ) == ObjectIdenfier::kLight ||
						findObj->GetIdenfier( ) == ObjectIdenfier::kCamera ||
						findObj->GetIdenfier( ) == ObjectIdenfier::kPickTile )
					{
						MessageBox( this->GetWindowHandle( ),
							L"지울 수 없는 객체입니다.",
							L"WARNING!",
							MB_OK | MB_ICONEXCLAMATION
						);
						break;
					}

					cGameObjectManager::Get( )->DeleteObject( selectedObjName );
					ListView_DeleteItem( m_listHandle, selectedItemIndex );
				}
			}
		}
		break;
	}
}

cGameObject* HierarchyWindow::GetSelectedItemAsObject( )
{
	if ( !m_listHandle )
	{
		return nullptr;
	}

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
	if ( !m_listHandle )
	{
		return;
	}


	ListView_GetItemText( m_listHandle,
		this->GetSelectedItemIndex( ),
		0,
		outText,
		maxCount );
}

int32_t HierarchyWindow::GetSelectedItemIndex( ) const
{
	if ( !m_listHandle )
	{
		return -1;
	}

	int32_t index = ListView_GetNextItem( m_listHandle,
		-1, LVNI_ALL | LVNI_SELECTED );

	return index;
}

int32_t HierarchyWindow::GetListItemCount( ) const
{
	if ( !m_listHandle )
	{
		return 0;
	}

	return ListView_GetItemCount( m_listHandle );
}

void HierarchyWindow::AddListItem( 
	const std::wstring& itemName )
{
	if ( !m_listHandle )
	{
		return;
	}

	LVITEMW lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = m_layer;
	lvItem.iSubItem = 0;
	lvItem.pszText = const_cast<wchar_t*>( itemName.c_str( ));
	ListView_InsertItem( m_listHandle, &lvItem );

	++m_layer;
}

void HierarchyWindow::ResetListItem( )
{
	if ( !m_listHandle )
	{
		return;
	}

	int listItemCount = this->GetListItemCount( );
	for ( int i = 0; i < listItemCount; ++i )
	{
		wchar_t currObjName[256]{ 0 };
		
		ListView_GetItemText( 
			m_listHandle,
			i, 0,
			currObjName, 
			256
		);

		if ( currObjName )
		{
			auto* obj = cGameObjectManager::Get( )->FindObject( currObjName );
			if ( obj->GetIdenfier( ) != ObjectIdenfier::kLight &&
				obj->GetIdenfier( ) != ObjectIdenfier::kCamera )
			{
				ListView_DeleteItem( m_listHandle, i-- );
				--listItemCount;
			}
		}
	}
}

void HierarchyWindow::SetupListView( HWND wndHandle )
{
	RECT rt;
	GetClientRect( wndHandle, &rt );

	m_listHandle = CreateWindowEx( 
		NULL, 
		WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LVS_REPORT | LVS_SINGLESEL | LVS_EDITLABELS, -1, -1, rt.right+2, rt.bottom+2,
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

