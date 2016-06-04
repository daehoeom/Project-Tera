#include "stdafx.h"
#include "DirectInput.h"

cDirectInput::cDirectInput( )
{
}

cDirectInput::~cDirectInput( )
{
	if ( m_directInput != NULL ) {
		m_directInput->Release( );
		m_directInput = NULL;
	}

	// Keyboard
	if ( m_pKeyboard )
		m_pKeyboard->Unacquire( );

	if ( m_pKeyboard != NULL ) {
		m_pKeyboard->Release( );
		m_pKeyboard = NULL;
	}

	// Mouse
	if ( m_pMouse )
		m_pMouse->Unacquire( );

	if ( m_pKeyboard != NULL ) {
		m_pKeyboard->Release( );
		m_pKeyboard = NULL;
	}
}

bool cDirectInput::Setup( HWND hWnd )
{
	HRESULT hr;
	m_wndHandle = hWnd;

	if ( FAILED( hr = DirectInput8Create(
		GetModuleHandle( NULL ), 
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, ( void** )&m_directInput, NULL ))) {
		MessageBox( m_wndHandle, L"DirectInput8Create( ) Initialize Error.", L"WARNING!", MB_OK | MB_ICONEXCLAMATION );
		ErrorHandling( hr );
	}

	// Keyboard
	if ( FAILED( hr = m_directInput->CreateDevice( GUID_SysKeyboard, &m_pKeyboard, NULL )) ||
			FAILED( hr = m_pKeyboard->SetDataFormat( &c_dfDIKeyboard )) ||
				FAILED( hr = m_pKeyboard->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ))) {
		ErrorHandling( hr );
		return false;
	}

	// Mouse
	if ( FAILED( hr = m_directInput->CreateDevice( GUID_SysMouse, &m_pMouse, NULL )) ||
			FAILED( hr = m_pMouse->SetDataFormat( &c_dfDIMouse2 )) ||
				FAILED( hr = m_pMouse->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ))) {
		ErrorHandling( hr );
		return false;
	}
	return true;
}

void cDirectInput::Update( )
{
	HRESULT hr;
	if ( m_pKeyboard == NULL || m_pMouse == NULL )
		return;

	// Keyboard
	memcpy( m_OldKeys, m_CurKeys, sizeof( BYTE )*256 );
	m_OldMouseState = m_CurMouseState;

	memset( &m_CurKeys, 0, sizeof( m_CurKeys ));
	hr = m_pKeyboard->GetDeviceState( sizeof( m_CurKeys ), m_CurKeys );
	if ( FAILED( hr )) {
		hr = m_pKeyboard->Acquire( );
		while ( hr == DIERR_INPUTLOST )
			hr = m_pKeyboard->Acquire( );
	}
	
	// Mouse
	memset( &m_CurMouseState, 0, sizeof( m_CurMouseState ));
	hr = m_pMouse->GetDeviceState( sizeof( m_CurMouseState ), &m_CurMouseState );
	if ( FAILED( hr )) { 
		hr = m_pMouse->Acquire( );
		while ( hr == DIERR_INPUTLOST )
			hr = m_pMouse->Acquire( );
	}
}

POINT cDirectInput::GetCurrentCursorPos( )
{
	RECT rt;
	POINT pt;
	GetWindowRect( m_wndHandle, &rt );
	GetCursorPos( &pt );

	m_MousePos.x = pt.x - rt.left;
	m_MousePos.y = pt.y - rt.top;

	return m_MousePos;
}

bool cDirectInput::GetKeyboardState( int KeyState, BYTE key )
{
	if ( GetFocus( ) != m_wndHandle )
		return false;

	switch ( KeyState )
	{
	case KeyState::DOWN:
		if ( m_CurKeys[key] & 0x80 && !( m_OldKeys[key] & 0x80 ))
			return true;
		return false;

	case KeyState::UP:
		if ( !( m_CurKeys[key] & 0x80 ) && m_OldKeys[key] & 0x80 )
			return true;
		return false;

	case KeyState::PRESS:
		if ( m_CurKeys[key] & 0x80 && m_OldKeys[key] & 0x80 )
			return true;
		return false;
	}
	return false;
}

bool cDirectInput::GetMouseState( int KeyState, int MouseType )
{
	if ( GetFocus( ) != m_wndHandle )
		return false;

	switch ( KeyState )
	{
	case KeyState::DOWN:
		if ( !( m_OldMouseState.rgbButtons[MouseType] == 0x80 ) &&
			m_CurMouseState.rgbButtons[MouseType] == 0x80 )
			return true;
		return false;

	case KeyState::UP:
		if ( m_OldMouseState.rgbButtons[MouseType] == 0x80 &&
			!( m_CurMouseState.rgbButtons[MouseType] == 0x80 ))
			return true;
		return false;

	case KeyState::PRESS:
		if ( m_OldMouseState.rgbButtons[MouseType] == 0x80 &&
			m_CurMouseState.rgbButtons[MouseType] == 0x80 )
			return true;
		return false;
	}
	return false;
}

void cDirectInput::ErrorHandling( HRESULT result )
{
	if ( result == S_OK )
		return;

	void* lpBuf;
	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError( ),
			MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), ( LPWSTR )&lpBuf, 0, NULL );
	
	wchar_t Buf[256];
	wsprintf( Buf, L"DirectInput Initialize Error. ( %s )", ( LPWSTR )lpBuf );
	MessageBox( NULL, ( LPCWSTR )Buf, L"WARNING!", MB_OK | MB_ICONEXCLAMATION );

	LocalFree( lpBuf );
}
