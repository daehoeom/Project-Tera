#pragma once
#include "AbstractWindow.h"


class MainSurfaceWindow :
	public AbstractWindow,
	public IWindowDelegate
{
public:
	MainSurfaceWindow( );
	virtual ~MainSurfaceWindow( );
	
	// Event handler
	virtual void OnIdle( ) override;

	// delegate
	virtual void OnMove( AbstractWindow* sender, int x, int y );
	virtual void OnSize( AbstractWindow* sender, int width, int height );

protected:
	static LRESULT CALLBACK MsgProc( HWND, UINT, WPARAM, LPARAM );
	virtual HWND SetupWindowComponents( ) override;

private:
	wchar_t* m_dropQueryPath;
	void SetupWindowClass( );
	POINT m_prevPos;
	HWND SetupWindow( );
};

