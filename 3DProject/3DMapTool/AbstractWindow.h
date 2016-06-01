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
	// Sets
	void SetOwner( AbstractWindow* owner );
	void SetPosition(int x, int y );
	void SetChild( AbstractWindow* child );
	void Move( int x, int y );
	
	// Gets
	AbstractWindow* GetOwner( );
	void GetSize( _Out_ int * width, _Out_ int * height );
	void GetPosition( _Out_ int * x, _Out_ int * y );
	std::vector<AbstractWindow*>& GetChildRepo( );

	const std::wstring& GetClassName( ) const { return m_wndClassName; }
	const std::wstring& GetName( ) const { return m_wndName; }
	HWND GetHWND( ) const { return m_myWndHandle; }

protected:
	virtual HWND SetupWindowComponents( ) = 0;

private:
	HWND m_myWndHandle;
	std::wstring m_wndName;
	std::wstring m_wndClassName;
	AbstractWindow* m_owner = nullptr;
	std::vector<AbstractWindow*> m_childRepo;
};

inline void AbstractWindow::SetOwner( 
	AbstractWindow * owner )
{
	m_owner = owner;
}

inline void AbstractWindow::SetPosition( int x, int y )
{
	SetWindowPos( m_myWndHandle, NULL, x, y, 0, 0, SWP_NOSIZE );
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

	SetWindowPos( m_myWndHandle, NULL, currX+x, currY+y, 0,0, SWP_NOSIZE );
}

class IWindowDelegate
{
public:
	virtual void OnMove( AbstractWindow* sender, int x, int y ) {}
	virtual void OnSize( AbstractWindow* sender, int width, int height ) {}
};
