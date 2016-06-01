//#pragma once
//#include "AbstractWindow.h"
//
//
//class InspectorWindow :
//	public AbstractWindow
//{
//public:
//	InspectorWindow( );
//	virtual ~InspectorWindow( );
//
//	// Event handler
//	virtual void OnIdle( ) override;
//	void SetDelegate( IWindowDelegate* windowDelegate );
//
//protected:
//	static LRESULT CALLBACK MsgProc( HWND, UINT, WPARAM, LPARAM );
//	virtual HWND SetupWindowComponents( ) override;
//
//private:
//	void SetupWindowClass( );
//	HWND SetupWindow( );
//	void SetupList( );
//
//private:
//	HWND m_listHandle;
//	LVITEM m_lvItem;
//	LVCOLUMN m_lvCol;
//	POINT m_prevPos;
//	IWindowDelegate* m_wndDelegate = nullptr;
//};
//
