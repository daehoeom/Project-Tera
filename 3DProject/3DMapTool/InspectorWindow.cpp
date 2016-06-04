#include "stdafx.h"
#include "InspectorWindow.h"

#include "resource.h"


HWND g_inspectorWndHandle;

InspectorWindow::InspectorWindow( HWND parentWndHandle ) :
	AbstractWindow( parentWndHandle ),
	m_currSelectedItem( -1 )
{
}

InspectorWindow::~InspectorWindow( )
{
	DestroyWindow( this->GetWindowHandle( ));
}

void InspectorWindow::OnIdle( )
{
}

int32_t InspectorWindow::GetCurrSelectedItem( ) const
{
	return m_currSelectedItem;
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
		}
		break;
	
	case WM_NCLBUTTONDOWN:
		return -1;
	}

	return 0;
}
