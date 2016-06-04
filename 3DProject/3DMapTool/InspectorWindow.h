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

	int32_t GetCurrSelectedItem( ) const;
	void SetPositionData( const D3DXVECTOR3& pos );
	void SetRotationData( const D3DXVECTOR3& rot );
	void SetScaleData( const D3DXVECTOR3& scale );
	
protected:
	virtual LRESULT MessageProc( HWND, UINT, WPARAM, LPARAM ) override;

private:
	int32_t m_currSelectedItem;
	IWindowDelegate* m_wndDelegate = nullptr;
};

