#include "stdafx.h"
#include "AbstractWindow.h"

#include "resource.h"


AbstractWindow::AbstractWindow( 
	HWND parentWndHandle ) :

	m_isDialog( true ),
	m_parentWndHandle( parentWndHandle )
{
}

AbstractWindow::AbstractWindow(
	const wchar_t* wndName,
	DWORD exStyle,
	DWORD normalStyle,
	HWND parentWndHandle,
	const WNDCLASSEXW& wndClassEx,
	int x,
	int y,
	int width,
	int height ) :
	
	m_owner( nullptr ),
	m_wndDelegate( nullptr ),
	m_wndName( wndName ),
	m_wndHandle( nullptr ),
	m_wndClassName( wndClassEx.lpszClassName ),
	m_x( x ),
	m_y( y ),
	m_width ( width ),
	m_height( height ),
	m_exStyle( exStyle ),
	m_parentWndHandle( parentWndHandle ),
	m_normalStyle( normalStyle ),
	m_wndClassEx( wndClassEx ),
	m_isDialog( false )
{
}

AbstractWindow::~AbstractWindow( )
{
	DestroyWindow( m_wndHandle );
}

void AbstractWindow::SetupWindowComponents( )
{
	// Dialog window
	if ( m_isDialog )
	{
		this->CreateDialogWindow( );
	}
	// Custom create window
	else
	{
		this->CreateWindow( 
			m_exStyle, 
			m_normalStyle, 
			m_x, 
			m_y, 
			m_width, 
			m_height 
		);
	} 

	if ( !m_wndHandle )
	{
		MessageBox(
			GetFocus( ),
			L"Failed to create window.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
	}
}

LRESULT AbstractWindow::MsgProcImpl(
	AbstractWindow* window, 
	HWND wndHandle,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam )
{
	switch ( msg )
	{
	case WM_DESTROY:
		// Save window ptr to window-personal storage
		SetWindowLongPtrW( wndHandle, GWLP_USERDATA, 0 );
		PostQuitMessage( 0 );
		return 0;

	default:
		return window->MessageProc( wndHandle, msg, wParam, lParam );
	}

}

INT_PTR AbstractWindow::DlgMsgProc( 
	HWND wndHandle,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam )
{
	AbstractWindow* extraMemAsWindow = reinterpret_cast<AbstractWindow*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));

	if ( extraMemAsWindow )
	{
		return MsgProcImpl( extraMemAsWindow, wndHandle, msg, wParam, lParam );
	}
	else
	{
		if ( msg == WM_INITDIALOG )
		{
			extraMemAsWindow = reinterpret_cast<AbstractWindow*>(
				lParam );
			extraMemAsWindow->m_wndHandle = wndHandle;
			return extraMemAsWindow->MessageProc(
				wndHandle, msg, wParam, lParam );
		}
		else
		{
			return 0;
		}
	}
}

LRESULT CALLBACK AbstractWindow::MsgProc(
	HWND wndHandle, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam )
{
	AbstractWindow* extraMemAsWindow = reinterpret_cast<AbstractWindow*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));

	if ( extraMemAsWindow )
	{
		return MsgProcImpl( extraMemAsWindow, wndHandle, msg, wParam, lParam );
	}
	else
	{
		if ( msg == WM_CREATE )
		{
			extraMemAsWindow = reinterpret_cast<AbstractWindow*>(
				LPCREATESTRUCT( lParam )->lpCreateParams );
			extraMemAsWindow->m_wndHandle = wndHandle;
			
			return extraMemAsWindow->MessageProc(
				wndHandle, msg, wParam, lParam );
		}
		else
		{
			return DefWindowProc( wndHandle, msg, wParam, lParam );
		}
	}
}

void AbstractWindow::CreateDialogWindow( )
{
	m_wndHandle = CreateDialogParam(
		GetModuleHandle( nullptr ),
		MAKEINTRESOURCE( IDD_INSPECTOR ),
		m_parentWndHandle,
		DlgMsgProc,
		reinterpret_cast<LPARAM>( this )
	);

	SetWindowLongPtrW(
		m_wndHandle,
		GWLP_USERDATA, // Save window ptr to window-personal storage
		reinterpret_cast<LONG_PTR>( this )
	);

	ShowWindow( m_wndHandle, SW_SHOW );
}

void AbstractWindow::CreateWindow(
	DWORD exStyle, 
	DWORD normalStyle, 
	int x, 
	int y, 
	int width, 
	int height )
{
	WNDCLASSEX modifiedWndClass = m_wndClassEx;
	modifiedWndClass.cbWndExtra = sizeof( uintptr_t );
	modifiedWndClass.lpszClassName = m_wndClassName.c_str( );
	modifiedWndClass.lpfnWndProc = AbstractWindow::MsgProc;
	RegisterClassExW( &modifiedWndClass );

	CreateWindowExW(
		exStyle,
		m_wndClassName.c_str(),
		m_wndName.c_str(),
		normalStyle,
		x,
		y,
		width,
		height,
		m_parentWndHandle,
		nullptr, 
		GetModuleHandle( nullptr ), 
		this
	);

	SetWindowLongPtrW(
		m_wndHandle,
		GWLP_USERDATA, // Save window ptr to window-personal storage
		reinterpret_cast<LONG_PTR>( this )
	);

	ShowWindow( m_wndHandle, SW_SHOW );
	UpdateWindow( m_wndHandle );
}
