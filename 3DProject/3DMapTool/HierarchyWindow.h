#pragma once
#include "AbstractWindow.h"


class HierarchyWindow :
	public AbstractWindow
{
public:
	HierarchyWindow( );
	virtual ~HierarchyWindow( );

	// Event handler
	virtual void OnIdle( ) override;
	
	void AddListItem( const wchar_t* itemName );

protected:
	LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;

private:
	WNDCLASSEXW MakeWindowClass( );
	void SetupList( HWND wndHandle );

private:
	HWND m_listHandle;
	int m_Layer = 0;
	LVITEM m_lvItem;
	LVCOLUMN m_lvCol;
	POINT m_prevPos;
	IWindowDelegate* m_wndDelegate = nullptr;
};

