#pragma once
#include "AbstractWindow.h"


class HierarchyWindow :
	public AbstractWindow
{
public:
	HierarchyWindow( HWND parentWndHandle );
	virtual ~HierarchyWindow( );

	// Event handler
	virtual void OnIdle( ) override;
	
	void AddListItem( const std::wstring& itemName );
	
	void GetSelectedItemText( wchar_t* outText, int32_t maxCount ) const;
	int32_t GetSelectedItemIndex( ) const;

protected:
	LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;

private:
	WNDCLASSEXW MakeWindowClass( );
	void SetupList( HWND wndHandle );

private:
	HWND m_listHandle;
	int m_currSelectedItem;
	int m_layer = 0;
	POINT m_prevPos;
	IWindowDelegate* m_wndDelegate = nullptr;
};

