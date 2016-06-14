#pragma once
#include "Singleton.h"

class cCamera : 
	public TSingleton<cCamera>
{
public:
	void Update( );
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	D3DXVECTOR3 GetEye() { return m_vEye; }

public:
	void SetFollowingTarget( class cGameObject* );

protected:
	cCamera( );
	virtual ~cCamera( );

private:
	void SetupProjection( float fovy, float nearZ, float farZ );
	void SetupView( const D3DXVECTOR3& eye, const D3DXVECTOR3& lookAt );

private:
	const float		m_cameraHeight;
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3		m_vLookAt;
	bool			m_isLButtonDown;
	float			m_fRotX;
	float			m_fRotY;
	POINT			m_ptPrevMouse;
	float			m_fDist;
	cGameObject*	m_followTarget;
};

inline void cCamera::SetFollowingTarget( 
	cGameObject* followingTarget )
{
	m_followTarget = followingTarget;
}
