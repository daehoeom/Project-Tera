#include "StdAfx.h"
#include "cCamera.h"

#include "DirectInput.h"
#include "cDeviceManager.h"

cCameraObject::cCameraObject( 
	HWND wndHandle, const std::wstring& objName )
	: m_vEye(0.f, 0.f, -1.f)
	, m_vUp(0.f, 1, 0.f)
	, m_vLookAt(0.f, 0.f, 0.f)
	, m_isLButtonDown(false)
	, m_fRotX(0.0f)
	, m_fRotY(0.0f)
	, m_fDist(1.f)
	, m_target( nullptr )
	, cGameObject( objName )
{
	m_ownerWndHandle = wndHandle;

	RECT rc;
	GetClientRect( wndHandle, &rc );
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4.0f, rc.right / ( float )rc.bottom, 1, 3000 );
	g_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

cCameraObject::~cCameraObject(void)
{
}

void cCameraObject::Update()
{
	m_vEye = D3DXVECTOR3(0, 0, -m_fDist);
	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fRotX);
	D3DXMatrixRotationY(&matRotY, m_fRotY);
	D3DXMATRIXA16 matRot = matRotX * matRotY;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRot);

	this->UpdateInput( matRot );

	m_vEye = m_vEye + this->GetPosition( );
	m_vLookAt = this->GetPosition( );

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

}

void cCameraObject::SetTarget( cGameObject * target )
{
	m_target = target;
}

void cCameraObject::UpdateInput( const D3DXMATRIXA16& matRot )
{
	float speed = 0.3;
	if ( cDirectInput::Get( )->GetKeyboardState(
		KeyState::PRESS, DIK_LSHIFT ) )
	{
		speed = 1.f;
	}

	// Keyboard
	if ( cDirectInput::Get( )->GetKeyboardState(
		KeyState::PRESS, DIK_W ))
	{
		D3DXVECTOR3 vDir{0.f,0.f,speed};
		D3DXVec3TransformNormal( &vDir, &vDir, &matRot );

		this->Move( vDir );
	}
	if ( cDirectInput::Get( )->GetKeyboardState(
		KeyState::PRESS, DIK_S ))
	{
		D3DXVECTOR3 vDir{0.f,0.f,-speed};
		D3DXVec3TransformNormal( &vDir, &vDir, &matRot );

		this->Move( vDir );
	}

	// Mouse
	const LONG mouseWheelDelta = cDirectInput::Get( )->GetCurrMouseState( ).lZ;
	if ( mouseWheelDelta != 0 )
	{
		m_fDist -= mouseWheelDelta / 100.0f;
	}

	if ( cDirectInput::Get( )->GetMouseState(
			KeyState::DOWN, MouseType::RIGHT ) )
	{
		POINT currPos;
		GetCursorPos( &currPos );

		m_isLButtonDown = true;
		m_ptPrevMouse.x = currPos.x;
		m_ptPrevMouse.y = currPos.y;
	}
	else if ( cDirectInput::Get( )->GetMouseState(
			KeyState::UP, MouseType::RIGHT ) )
	{
		m_isLButtonDown = false;
	}
	
	if (m_isLButtonDown)
	{
		POINT ptCurrMouse;
		GetCursorPos( &ptCurrMouse );

		m_fRotX += (ptCurrMouse.y - m_ptPrevMouse.y) / 100.0f;
		m_fRotY += (ptCurrMouse.x - m_ptPrevMouse.x) / 100.0f;
		m_ptPrevMouse = ptCurrMouse;
		if (m_fRotX >= D3DX_PI / 2.0f - EPSILON)
		{
			m_fRotX = D3DX_PI / 2.0f - EPSILON;
		}
		if (m_fRotX <= -D3DX_PI / 2.0f + EPSILON)
		{
			m_fRotX = -D3DX_PI / 2.0f + EPSILON;
		}
	}
}
