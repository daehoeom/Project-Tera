#pragma once


#ifdef GetClassName
	#undef GetClassName
#endif

class AbstractWindow
{
public:
	AbstractWindow( const wchar_t* wndName );
	virtual ~AbstractWindow( ) = 0;

public:
	void Setup( );

	// Event Handler
	virtual void OnIdle( ) = 0;

public:
	void GetSize( _Out_ int * width, _Out_ int * height );
	void GetPosition( _Out_ int * x, _Out_ int * y );

	const std::wstring& GetClassName( ) const { return m_wndClassName; }
	const std::wstring& GetName( ) const { return m_wndName; }
	HWND GetHWND( ) const { return m_myWndHandle; }

protected:
	virtual HWND SetupWindowComponents( ) = 0;

private:
	HWND m_myWndHandle;
	std::wstring m_wndName;
	std::wstring m_wndClassName;
};

class IWindowDelegate
{
public:
	virtual void OnMove( AbstractWindow* sender ) {}
	virtual void OnSize( AbstractWindow* sender ) {}
};