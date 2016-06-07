#pragma once
#include "AbstractWindow.h"
#include "cObjLoader.h"

class MainSurfaceWindow :
	public AbstractWindow
{
public:
	MainSurfaceWindow( );
	virtual ~MainSurfaceWindow( );
	
	// Event Handler
	virtual void OnIdle( ) override;
	void OnDropFile( HDROP dropHandle );
	void OnSaveAsClicked( );
	void OnLoadMapClicked( );
	void OnNewSceneClicked( );

	// Deletgate
	virtual void OnMove( AbstractWindow* sender, int x, int y );
	virtual void OnSize( AbstractWindow* sender, int width, int height );

protected:
	LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;
	
private:
	WNDCLASSEXW MakeWindowClass( );

private:
	std::unique_ptr<char[]> m_dropQueryPath;
	POINT m_prevPos;
	int m_createCount;
};

