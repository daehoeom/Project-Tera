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

	void SetTarget( cGameObject* target );
	virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kCamera; }

private:
	void UpdateInput( const D3DXMATRIXA16& matRot );

private:
	cGameObject* m_target;
	HWND m_ownerWndHandle;
	const D3DXVECTOR3 m_vUp;
	D3DXVECTOR3	m_vLookAt;
	D3DXVECTOR3	m_vEye;
	bool		m_isLButtonDown;
	POINT		m_ptPrevMouse;
};

