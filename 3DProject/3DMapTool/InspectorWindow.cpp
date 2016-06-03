#include "stdafx.h"
#include "InspectorWindow.h"

#include "resource.h"

HWND g_hierarchyWndHandle;

InspectorWindow::InspectorWindow( HWND parentWndHandle ) :
	AbstractWindow(
		L"Inspector",
		NULL,
		WS_CAPTION,
		parentWndHandle,
		this->MakeWindowClass( ),
		0,
		0,
		InspectorWindowWidth,
		InspectorWindowHeight )
{
}

InspectorWindow::~InspectorWindow( )
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
	case WM_CREATE:
		{
			int ownerX, ownerY, ownerWidth, ownerHeight;
			this->GetOwner( )->GetPosition( &ownerX, &ownerY );
			this->GetOwner( )->GetSize( &ownerWidth, &ownerHeight );

			SetWindowPos( wndHandle, NULL, ownerX + ownerWidth,
				ownerY+(ownerHeight/2), 0, 0, SWP_NOSIZE );

			SetWindowPos( wndHandle, NULL, 0,
				0, InspectorWindowWidth, InspectorWindowHeight, SWP_NOMOVE );
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

WNDCLASSEXW InspectorWindow::MakeWindowClass( )
{
	WNDCLASSEXW wcex{ 0 };
	HINSTANCE instanceHandle( GetModuleHandle( nullptr ) );

	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = nullptr;
	wcex.hInstance = instanceHandle;
	wcex.hIcon = LoadIcon( instanceHandle, MAKEINTRESOURCE( IDI_MY3DMAPTOOL ) );
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszClassName = L"InspectorWindowClass";
	wcex.hIconSm = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	return wcex;
}

void InspectorWindow::OnIdle( )
{
}
