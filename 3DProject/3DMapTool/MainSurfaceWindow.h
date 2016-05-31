#pragma once
#include "IWindow.h"


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
	virtual void OnMove( AbstractWindow* sender ) {}
	virtual void OnSize( AbstractWindow* sender ) {}

protected:
	static LRESULT CALLBACK MsgProc( HWND, UINT, WPARAM, LPARAM );
	virtual HWND SetupWindowComponents( ) override;

private:
	void SetupWindowClass( );
	HWND SetupWindow( );
	void InitD3DSurface( );
};

