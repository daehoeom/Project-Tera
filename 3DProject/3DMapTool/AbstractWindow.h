#pragma once

#ifdef CreateWindow
#	undef CreateWindow
#endif
#ifdef GetClassName
#	undef GetClassName
#endif

class AbstractWindow;
class IWindowDelegate
{
public:
	virtual void OnMove( AbstractWindow* sender, int x, int y ) {}
	virtual void OnSize( AbstractWindow* sender, int width, int height ) {}
};

class AbstractWindow :
	public IWindowDelegate
{
public:
	// For dialog
	explicit AbstractWindow( 
		HWND parentWndHandle );
	
	// General creation
	explicit AbstractWindow(
		const wchar_t* wndName,
		DWORD exStyle,
		DWORD normalStyle,
		HWND parentWndHandle,
		const WNDCLASSEXW& wndClass,
		int x,
		int y,
		int width,
		int height
	);
	
	virtual ~AbstractWindow( ) = 0;

	// Event Handler
	virtual void OnIdle( ) = 0;
	virtual LRESULT OnDroppedFile( HDROP dropHandle ) { return 0; }

	void SetupWindowComponents( );

	/* 
		Sets
	*/
	void SetOwner( AbstractWindow* owner );
	void SetPosition( int x, int y );
	void SetDelegate( IWindowDelegate* wndDelegate );
	void AddChild( AbstractWindow* child );
	void Move( int x, int y );
	
	/* 
		Gets
	*/
	std::wstring GetTitle( );
	void GetSize( _Out_ int* width, _Out_ int* height );
	void GetPosition( _Out_ int* x, _Out_ int* y );
	
	AbstractWindow* GetOwner( );
	const AbstractWindow* GetOwner( ) const;
	HWND GetWindowHandle( ) const;
	const std::wstring& GetName( ) const;
	const std::wstring& GetClassName( ) const;
	

protected:
	std::vector<AbstractWindow*>& GetChildRepo( );

private:
	static INT_PTR CALLBACK DlgMsgProc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK MsgProc( HWND, UINT, WPARAM, LPARAM );
	// Real processor
	static LRESULT MsgProcImpl( AbstractWindow*, HWND, UINT, WPARAM, LPARAM );
	// Non-static message procedure ( Pure virtual )
	virtual LRESULT MessageProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam ) = 0;
	
	void CreateDialogWindow( );
	void CreateWindow( DWORD exStyle, 
		DWORD normalStyle, 
		int x, 
		int y, 
		int width, 
		int height );

private:
	// Window info
	HWND m_wndHandle;
	std::wstring m_wndName;
	std::wstring m_wndClassName;
	DWORD m_exStyle;
	DWORD m_normalStyle;
	HWND m_parentWndHandle;
	WNDCLASSEXW m_wndClassEx;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	const bool m_isDialog;

	// About hierarchy
	AbstractWindow* m_owner;
	IWindowDelegate* m_wndDelegate;
	std::vector<AbstractWindow*> m_childRepo;
};

inline void AbstractWindow::SetOwner( 
	AbstractWindow * owner )
{
	m_owner = owner;
}

inline void AbstractWindow::SetPosition( int x, int y )
{
	SetWindowPos( m_wndHandle, NULL, x, y, 0, 0, SWP_NOSIZE );
}

inline void AbstractWindow::SetDelegate( 
	IWindowDelegate* wndDelegate )
{
	m_wndDelegate = wndDelegate;
}

inline AbstractWindow* AbstractWindow::GetOwner( )
{
	return m_owner;
}

inline const AbstractWindow* AbstractWindow::GetOwner( ) const
{
	return m_owner;
}

inline std::wstring AbstractWindow::GetTitle( )
{
	wchar_t buf[128];
	GetWindowText( m_wndHandle, buf, 128 );

	return std::wstring( buf );
}

inline void AbstractWindow::GetSize( int* width, int* height )
{
	RECT rt;
	GetClientRect( m_wndHandle, &rt );

	*width = rt.right;
	*height = rt.bottom;
}

inline void AbstractWindow::GetPosition( int* x, int* y )
{
	RECT rt;
	GetWindowRect( m_wndHandle, &rt );

	*x = rt.left;
	*y = rt.top;
}

inline std::vector<AbstractWindow*>& AbstractWindow::GetChildRepo( )
{
	return m_childRepo;
}

inline void AbstractWindow::AddChild( 
	AbstractWindow * child )
{
	m_childRepo.push_back( child );
}

inline void AbstractWindow::Move( int x, int y )
{
	int currX, currY;
	this->GetPosition( &currX, &currY );

	SetWindowPos( m_wndHandle, NULL, currX+x, currY+y, 0,0, SWP_NOSIZE );
}

inline HWND AbstractWindow::GetWindowHandle( ) const
{
	assert( m_wndHandle &&
		"GetWindowHandle invoked but returning handle pointer address is zero." );

	return m_wndHandle;
}

inline const std::wstring & AbstractWindow::GetName( ) const
{
	return m_wndName;
}

inline const std::wstring & AbstractWindow::GetClassName( ) const
{
	return m_wndClassName;
}
