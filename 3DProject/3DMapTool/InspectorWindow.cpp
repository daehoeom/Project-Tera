#include "stdafx.h"
#include "InspectorWindow.h"

#include "resource.h"
#include "cGameObjectManager.h"
#include "Console.h"

HWND g_inspectorWndHandle;

WNDPROC orgButtonProc;
LRESULT CALLBACK buttonSubProc( HWND wndHandle,
	UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	case WM_KEYDOWN:
		{
			if ( wParam != VK_RETURN ||
				g_hierarchyWnd->GetSelectedItemIndex() < 0 )
			{
				break;
			}

			wchar_t buf[256] {0};
			g_hierarchyWnd->GetSelectedItemText( buf, 256 );
			if ( buf[0] == L'\0' )
				break;
			

			// POSITION
			if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITXPOS ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITXPOS, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetPosition( {
						( float )_wtof( dlgItemText ),
						object->GetPosition( ).y,
						object->GetPosition( ).z
					} );
				}
			}
			else if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITYPOS ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITYPOS, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetPosition( {
						object->GetPosition( ).x,
						( float )_wtof( dlgItemText ),
						object->GetPosition( ).z
					} );
				}
			}
			else if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITZPOS ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITZPOS, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetPosition( {
						object->GetPosition( ).x,
						object->GetPosition( ).y,
						( float )_wtof( dlgItemText )
					} );
				}
			}
			// ROTATION
			else if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITXROT ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITXROT, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetAngle( {
						( float )_wtof( dlgItemText ),
						object->GetAngle( ).y,
						object->GetAngle( ).z
					} );
				}
			}
			else if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITYROT ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITYROT, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetAngle( {
						object->GetAngle( ).x,
						( float )_wtof( dlgItemText ),
						object->GetAngle( ).z
					} );
				}
			}
			else if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITZROT ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITZROT, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetAngle( {
						object->GetAngle( ).x,
						object->GetAngle( ).y,
						( float )_wtof( dlgItemText )
					} );
				}
			}
			//SCALE
			else if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITXSCALE ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITXSCALE, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetScale( {
						( float )_wtof( dlgItemText ),
						object->GetScale( ).y,
						object->GetScale( ).z
					} );
				}
			}
			else if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITYSCALE ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITYSCALE, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetScale( {
						object->GetScale( ).x,
						( float )_wtof( dlgItemText ),
						object->GetScale( ).z
					} );
				}
			}
			else if ( wndHandle == GetDlgItem( 
				g_inspectorWnd->GetWindowHandle( ), IDC_EDITZSCALE ))
			{
				wchar_t dlgItemText[256]{ 0 };
				GetDlgItemText( g_inspectorWnd->GetWindowHandle( ),
					IDC_EDITZSCALE, dlgItemText, 256 );

				auto* object = cGameObjectManager::Get( )->FindObject(
					buf );
				if ( object )
				{
					object->SetScale( {
						object->GetScale( ).x,
						object->GetScale( ).y,
						( float )_wtof( dlgItemText )
					} );
				}
			}

			int n = 3;
		}
		break;
	}

	return CallWindowProc( orgButtonProc, wndHandle, msg, wParam, lParam );
}


InspectorWindow::InspectorWindow( HWND parentWndHandle ) :
	AbstractWindow( parentWndHandle )
{
}

InspectorWindow::~InspectorWindow( )
{
	DestroyWindow( this->GetWindowHandle( ));
}

void InspectorWindow::OnIdle( )
{
}


void InspectorWindow::SetPositionData(
	const D3DXVECTOR3& pos )
{
	const HWND dlgWndHandle = this->GetWindowHandle( );

	SetDlgItemText( dlgWndHandle, IDC_EDITXPOS, 
		std::to_wstring(pos.x).c_str());
	SetDlgItemText( dlgWndHandle, IDC_EDITYPOS, 
		std::to_wstring(pos.y).c_str());
	SetDlgItemText( dlgWndHandle, IDC_EDITZPOS, 
		std::to_wstring(pos.z).c_str());
}

void InspectorWindow::SetRotationData( 
	const D3DXVECTOR3 & rot )
{
	const HWND dlgWndHandle = this->GetWindowHandle( );

	SetDlgItemText( dlgWndHandle, IDC_EDITXROT, 
		std::to_wstring(rot.x).c_str());
	SetDlgItemText( dlgWndHandle, IDC_EDITYROT, 
		std::to_wstring(rot.y).c_str());
	SetDlgItemText( dlgWndHandle, IDC_EDITZROT, 
		std::to_wstring(rot.z).c_str());
}

void InspectorWindow::SetScaleData( 
	const D3DXVECTOR3& scale )
{
	const HWND dlgWndHandle = this->GetWindowHandle( );

	SetDlgItemText( dlgWndHandle, IDC_EDITXSCALE, 
		std::to_wstring(scale.x).c_str());
	SetDlgItemText( dlgWndHandle, IDC_EDITYSCALE, 
		std::to_wstring(scale.y).c_str());
	SetDlgItemText( dlgWndHandle, IDC_EDITZSCALE, 
		std::to_wstring(scale.z).c_str());
}

void InspectorWindow::SubclassMyDlgButton( HWND myWindowHandle )
{
	orgButtonProc = ( WNDPROC )SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITXPOS ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );
	SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITYPOS ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );
	SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITZPOS ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );

	SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITXROT ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );
	SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITYROT ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );
	SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITZROT ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );

	SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITXSCALE ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );
	SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITYSCALE ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );
	SetWindowLongPtr(
		GetDlgItem( myWindowHandle, IDC_EDITZSCALE ),
		GWLP_WNDPROC, ( LPARAM )buttonSubProc );
}

LRESULT InspectorWindow::MessageProc( 
	HWND wndHandle, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam )
{
	switch ( msg )
	{
	case WM_INITDIALOG:
		{
			int ownerX, ownerY, ownerWidth, ownerHeight;
			this->GetOwner( )->GetPosition( &ownerX, &ownerY );
			this->GetOwner( )->GetSize( &ownerWidth, &ownerHeight );

			SetWindowPos( wndHandle, nullptr, ownerX+ownerWidth, 
				ownerY, 0, 0, SWP_NOSIZE );

			this->SubclassMyDlgButton( wndHandle );
		}
		break;

	case WM_NCLBUTTONDOWN:
		return -1;
	}

	return 0;
}
