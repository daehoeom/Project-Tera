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
	void SetDelegate( IWindowDelegate* windowDelegate );
	void AddListItem( const wchar_t* itemName );

protected:
	static LRESULT CALLBACK MsgProc( HWND, UINT, WPARAM, LPARAM );
	virtual HWND SetupWindowComponents( ) override;

private:
	void SetupWindowClass( );
	HWND SetupWindow( );
	void SetupList( );

private:
	HWND m_listHandle;
	int m_Layer = 0;
	LVITEM m_lvItem;
	LVCOLUMN m_lvCol;
	POINT m_prevPos;
	IWindowDelegate* m_wndDelegate = nullptr;
};

