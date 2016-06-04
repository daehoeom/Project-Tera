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
		MessageBox( 0, 00, 0, 0 );
		break;
	case WM_LBUTTONDOWN:
		MessageBox( 0, 00, 0, 0 );
		break;
	}

	return 0;
}
