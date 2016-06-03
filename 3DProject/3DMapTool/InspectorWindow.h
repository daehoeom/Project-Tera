#pragma once
#include "AbstractWindow.h"


class InspectorWindow :
	public AbstractWindow
{
public:
	InspectorWindow( HWND parentWndHandle );
	virtual ~InspectorWindow( );

	// Event handler
	virtual void OnIdle( ) override;

protected:
	LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;

private:
	WNDCLASSEXW MakeWindowClass( );

private:
	POINT m_prevPos;
	IWindowDelegate* m_wndDelegate = nullptr;
};

