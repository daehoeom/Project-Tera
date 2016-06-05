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

	void SetPositionData( const D3DXVECTOR3& pos );
	void SetRotationData( const D3DXVECTOR3& rot );
	void SetScaleData( const D3DXVECTOR3& scale );

private:
	void SubclassMyDlgButton( HWND myWindowHandle );
	
protected:
	virtual LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;

private:
	IWindowDelegate* m_wndDelegate = nullptr;
};

