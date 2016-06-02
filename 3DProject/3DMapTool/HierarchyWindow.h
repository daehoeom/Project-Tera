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
	
	void AddListItem( const std::wstring& itemName );

protected:
	LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;

private:
	WNDCLASSEXW MakeWindowClass( );
	void SetupList( HWND wndHandle );

private:
	HWND m_listHandle;
	LVITEMW m_lvItem;
	int m_layer = 0;
	POINT m_prevPos;
	IWindowDelegate* m_wndDelegate = nullptr;
};

