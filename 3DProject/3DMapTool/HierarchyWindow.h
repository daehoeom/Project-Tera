#pragma once
#include "AbstractWindow.h"


class HierarchyWindow :
	public AbstractWindow
{
public:
	explicit HierarchyWindow( HWND parentWndHandle );
	virtual ~HierarchyWindow( );

	// Event handler
	virtual void OnIdle( ) override;
	void OnItemDoubleClicked( LPNMLISTVIEW );
	void OnItemClicked( LPNMLISTVIEW );

	// Sets
	void AddListItem( const std::wstring& itemName );
	void ResetListItem( );

	// Gets
	class cGameObject* GetSelectedItemAsObject( );
	void GetSelectedItemText( wchar_t* outText, int32_t maxCount ) const;
	int32_t GetSelectedItemIndex( ) const;
	int32_t GetListItemCount( ) const;

protected:
	LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;

private:
	WNDCLASSEXW MakeWindowClass( );
	void SetupListView( HWND wndHandle );

private:
	HWND m_listHandle;
	int m_currSelectedItem;
	int m_layer;
};

