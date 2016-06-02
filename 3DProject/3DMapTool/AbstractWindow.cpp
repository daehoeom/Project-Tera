#include "stdafx.h"
#include "AbstractWindow.h"

#include "resource.h"


AbstractWindow::AbstractWindow( 
	const wchar_t* wndName,
	DWORD exStyle,
	DWORD normalStyle,
	const WNDCLASSEXW& wndClassEx,
	int x,
	int y,
	int width,
	int height ) :
	
	m_owner( nullptr ),
	m_wndDelegate( nullptr ),
	m_wndName( wndName ),
	m_wndClassName( wndClassEx.lpszClassName ),
	m_x( x ),
	m_y( y ),
	m_width ( width ),
	m_height( height ),
	m_exStyle( exStyle ),
	m_normalStyle( normalStyle ),
	m_wndClassEx( wndClassEx )
{
}

AbstractWindow::~AbstractWindow( )
{
}

AbstractWindow* AbstractWindow::GetOwner( )
{
	return m_owner;
}

void AbstractWindow::GetSize( int* width, int* height )
{
	RECT rt;
	GetClientRect( m_wndHandle, &rt );

	*width = rt.right;
	*height = rt.bottom;
}

void AbstractWindow::GetPosition( int* x, int* y )
{
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	*x = rt.left;
	*y = rt.top;
}

void AbstractWindow::SetupWindowComponents( )
{
	WNDCLASSEX copyWndClass = m_wndClassEx;
	copyWndClass.lpszClassName = m_wndClassName.c_str();
	copyWndClass.lpfnWndProc = AbstractWindow::CallbackMsgProc;
	RegisterClassExW( &copyWndClass );

	this->CreateWindow( 
		m_exStyle, 
		m_normalStyle, 
		m_x, 
		m_y, 
		m_width, 
		m_height 
	);
}

std::vector<AbstractWindow*>& AbstractWindow::GetChildRepo( )
{
	return m_childRepo;
}

LRESULT CALLBACK AbstractWindow::CallbackMsgProc(
	HWND wndHandle, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam )
{
	AbstractWindow* extraMemAsWindow = reinterpret_cast<AbstractWindow*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));

	if ( extraMemAsWindow )
	{
		int n = 3;
		return extraMemAsWindow->MessageProc( wndHandle, msg, wParam, lParam );
	}
	else if ( msg == WM_CREATE )
	{
		int n = 3;
	}
	else
	{
	}

	return DefWindowProc( wndHandle, msg, wParam, lParam );
}

void AbstractWindow::CreateWindow(
	DWORD exStyle, 
	DWORD normalStyle, 
	int x, 
	int y, 
	int width, 
	int height )
{
	m_wndHandle = CreateWindowExW(
		exStyle,
		m_wndClassName.c_str(),
		m_wndName.c_str(),
		normalStyle,
		x,
		y,
		width,
		height,
		nullptr, 
		nullptr, 
		GetModuleHandle( nullptr ), 
		nullptr 
	);

	SetWindowLongPtrW(
		m_wndHandle,
		GWLP_USERDATA, // Save window ptr to window-personal storage
		reinterpret_cast<LONG_PTR>( this )
	);

	ShowWindow( m_wndHandle, SW_SHOW );
	UpdateWindow( m_wndHandle );
}
