#pragma once
#include "AbstractWindow.h"


class InspectorWindow :
	public AbstractWindow
{
public:
	explicit InspectorWindow( HWND parentWndHandle );
	virtual ~InspectorWindow( );

	// Event handler
	virtual void OnIdle( ) override;

protected:
	virtual LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;

private:
	IWindowDelegate* m_wndDelegate = nullptr;
};

