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

public:
	void SetupWindowComponents( );
	
	/* 
		Sets
	*/
	void SetOwner( AbstractWindow* owner );
	void SetPosition(int x, int y );
	void SetDelegate( IWindowDelegate* wndDelegate );
	void SetChild( AbstractWindow* child );
	void Move( int x, int y );
	
	/* 
		Gets
	*/
	std::wstring GetTitle( );
	void GetSize( _Out_ int * width, _Out_ int * height );
	void GetPosition( _Out_ int * x, _Out_ int * y );
	
	AbstractWindow* GetOwner( );
	HWND GetWindowHandle( ) const;
	const std::wstring& GetName( ) const;
	const std::wstring& GetClassName( ) const;
	
protected:
	virtual LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) = 0;
	AbstractWindow* GetChildByName( const std::wstring& name );
	std::vector<AbstractWindow*>& GetChildRepo( );

private:
	static LRESULT CALLBACK CallbackMsgProc( HWND, UINT, WPARAM, LPARAM );
	void CreateWindow(
		DWORD exStyle, 
		DWORD normalStyle, 
		int x, 
		int y, 
		int width, 
		int height
	);

private:
	// Window info
	HWND m_wndHandle;
	const std::wstring m_wndName;
	const std::wstring m_wndClassName;
	const DWORD m_exStyle;
	const DWORD m_normalStyle;
	const HWND m_parentWndHandle;
	const WNDCLASSEXW m_wndClassEx;
	const int m_x;
	const int m_y;
	const int m_width;
	const int m_height;


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

inline void AbstractWindow::SetChild( 
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
