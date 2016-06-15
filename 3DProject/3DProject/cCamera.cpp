#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
	: m_vEye(0, 0, -5)
	, m_vUp(0, 1, 0)
	, m_vLookAt(0, 0, 0)
	, m_isLButtonDown(false)
	, m_fRotX(0.0f)
	, m_fRotY(0.0f)
	, m_fDist(100)
	, m_followTarget( nullptr )
	, m_cameraHeight( 20.f )
{
	this->SetupProjection( D3DX_PI/4.0f, 1.f, 3000.f );
}

cCamera::~cCamera(void)
{
}

void cCamera::SetupProjection( 
	float fovy,
	float nearZ,
	float farZ )
{
	assert( g_hWnd );

	RECT rc;
	GetClientRect( g_hWnd, &rc );

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, fovy, rc.right/( float )rc.bottom, nearZ, farZ );
	g_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

void cCamera::SetupView( 
	const D3DXVECTOR3& eye, 
	const D3DXVECTOR3& lookAt )
{
	const D3DXVECTOR3 up( 0, 1, 0 );
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &eye, &lookAt, &up );
	g_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
}

void cCamera::Update( )
{
	m_vEye = D3DXVECTOR3(0, 0, -m_fDist);
	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fRotX);
	if ( m_followTarget )
	{
		D3DXMatrixRotationY(&matRotY, 
			m_followTarget->GetAngle( ).y + D3DXToRadian( 90 ));
	}
	D3DXMATRIXA16 matRot = matRotX * matRotY;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRot);
	
	if ( m_followTarget )
	{
		m_vEye = m_vEye + m_followTarget->GetPosition( );
		m_vLookAt = m_followTarget->GetPosition( );
		m_vLookAt.y += m_cameraHeight;
	}
	D3DXMATRIXA16 matView;

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONDOWN:
		m_isLButtonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONUP:
		m_isLButtonDown = false;
		break;
	case WM_MOUSEMOVE:
	{
		if (m_isLButtonDown)
		{
			POINT ptCurrMouse;
			ptCurrMouse.x = LOWORD(lParam);
			ptCurrMouse.y = HIWORD(lParam);
			m_fRotX += (ptCurrMouse.y - m_ptPrevMouse.y) / 100.0f;
			//m_fRotY += (ptCurrMouse.x - m_ptPrevMouse.x) / 100.0f;
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
	break;
	case WM_MOUSEWHEEL:
		m_fDist -= GET_WHEEL_DELTA_WPARAM(wParam) / 10;
		break;
	}
}