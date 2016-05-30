#pragma once
#include "Singleton.h"

class cCamera : 
	public TSingleton<cCamera>
{
public:
	void Update(D3DXVECTOR3* pTarget = NULL);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	cCamera( );
	~cCamera( );

private:
	D3DXVECTOR3	m_vEye;
	D3DXVECTOR3	m_vUp;
	D3DXVECTOR3	m_vLookAt;
	bool		m_isLButtonDown;
	float		m_fRotX;
	float		m_fRotY;
	POINT		m_ptPrevMouse;
	float		m_fDist;
};

