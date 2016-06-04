#include "stdafx.h"
#include "InspectorWindow.h"

#include "resource.h"


HWND g_inspectorWndHandle;

InspectorWindow::InspectorWindow( HWND parentWndHandle ) :
	AbstractWindow( parentWndHandle )
{
}

InspectorWindow::~InspectorWindow( )
{
	DestroyWindow( __super::GetWindowHandle( ));
}

void InspectorWindow::OnIdle( )
{
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
