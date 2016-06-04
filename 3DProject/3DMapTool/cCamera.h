#pragma once
#include "cGameObject.h"
#include "Singleton.h"

class cCameraObject :
	public cGameObject
{
public:
	cCameraObject( HWND wndHandle, const std::wstring& objName );
	virtual ~cCameraObject( );

	void Update( );
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetTarget( cGameObject* target );
	virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kCamera; }

private:
	void UpdateInput( );

private:
	cGameObject* m_target;
	HWND m_ownerWndHandle;
	D3DXVECTOR3	m_vEye;
	D3DXVECTOR3	m_vUp;
	D3DXVECTOR3	m_vLookAt;
	bool		m_isLButtonDown;
	float		m_fRotX;
	float		m_fRotY;
	POINT		m_ptPrevMouse;
	float		m_fDist;
};

