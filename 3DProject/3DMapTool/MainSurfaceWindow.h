#pragma once
#include "AbstractWindow.h"


class MainSurfaceWindow :
	public AbstractWindow
{
public:
	MainSurfaceWindow( );
	virtual ~MainSurfaceWindow( );
	
	// Event Handler
	virtual void OnIdle( ) override;

	// Deletgate
	virtual void OnMove( AbstractWindow* sender, int x, int y );
	virtual void OnSize( AbstractWindow* sender, int width, int height );

protected:
	LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;
	
private:
	WNDCLASSEXW MakeWindowClass( );

private:
	std::unique_ptr<wchar_t[]> m_dropQueryPath;
	POINT m_prevPos;
};

