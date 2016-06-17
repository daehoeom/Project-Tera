#pragma once
#include "Singleton.h"

class cCamera : 
	public TSingleton<cCamera>
{
public:
	void Update( );
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	const D3DXVECTOR3& GetEye( ) const { return m_vEye; }
	const D3DXVECTOR3& GetLookAt( ) const { return m_vLookAt; }
	const D3DXVECTOR3& GetUp( ) const { return m_vUp; }
	const D3DXMATRIXA16& GetView( ) const { return m_matView; }
	const D3DXMATRIXA16& GetProjection( ) const { return m_matProjection; }
	const D3DXMATRIXA16& GetViewProjection( ) const { return m_matProjection; }
	void SetFollowingTarget( class cGameObject* );

protected:
	cCamera( );
	virtual ~cCamera( );

private:
	void SetupProjection( float fovy, float nearZ, float farZ );
	void SetupView( const D3DXVECTOR3& eye, const D3DXVECTOR3& lookAt );

private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3		m_vLookAt;
	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProjection;
	D3DXMATRIXA16	m_matViewProjection;

	const float		m_cameraHeight;
	float			m_fRotX;
	float			m_fRotY;
	float			m_fDist;
	cGameObject*	m_followTarget;
	
	bool			m_isLButtonDown;
	POINT			m_ptPrevMouse;
};

inline void cCamera::SetFollowingTarget( 
	cGameObject* followingTarget )
{
	m_followTarget = followingTarget;
}
