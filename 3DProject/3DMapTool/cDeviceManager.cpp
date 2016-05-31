#include "stdafx.h"
#include "cDeviceManager.h"


cDeviceManager::cDeviceManager()
	: m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{
}


cDeviceManager::~cDeviceManager()
{
	//SAFE_RELEASE(m_pD3DDevice);


	if ( m_pD3DDevice )
	{
		ULONG ul = m_pD3DDevice->Release( );

		/*#ifdef _DEBUG*/
		assert( ul == 0 && "디바이스를 이용하여 생성한 객체 중 소멸되지 않은 객체가 있습니다." );
		

		/*#endif*/

	}
}

void cDeviceManager::Setup( 
	HWND wndHandle )
{
	assert( !m_pD3D && "cDeviceManager::Setup already invoked" );

	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	D3DCAPS9	stCaps;
	int			nVertexProcessing;
	m_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps );

	if ( stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory( &stD3DPP, sizeof( D3DPRESENT_PARAMETERS ) );
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;
	stD3DPP.hDeviceWindow = wndHandle;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D24X8;

	HRESULT hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		wndHandle,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice );

	if ( hr != D3D_OK )
	{
		// D3DERR_INVALIDCALL 메서드의 호출이 무효이다. 예를 들어, 메서드의 파라미터에 무효인 값이 설정되어 있는 경우 등이다.  
		// D3DERR_NOTAVAILABLE 이 장치는, 문의한 테크닉을 지원 하고 있지 않다.  
		// D3DERR_OUTOFVIDEOMEMORY Direct3D 가 처리를 실시하는데 충분한 디스플레이 
		switch ( hr )
		{
		case D3DERR_INVALIDCALL:
			//MessageBox(g_hWnd, "메서드의 호출이 무효이다. 예를 들어, 메서드의 파라미터에 무효인 값이 설정되어 있는 경우 등이다.");
			break;
		case D3DERR_NOTAVAILABLE:
			break;
		case D3DERR_OUTOFVIDEOMEMORY:
			break;
		}
	}
}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return m_pD3DDevice;
}
