#include "stdafx.h"
#include "ICollider.h"


#include "cDeviceManager.h"

ICollider::ICollider( ) :
#ifdef _DEBUG
	m_isDebugRender( true )
#else 
	m_isDebugRender( false )
#endif
{
}

void ICollider::PreRender( )
{
	g_pD3DDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_LIGHTING,FALSE );
	g_pD3DDevice->SetTexture( 0, nullptr );

	if ( m_isDebugRender )
	{
		g_pD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	}

}

void ICollider::PostRender( )
{
	g_pD3DDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_LIGHTING,
		TRUE );

	if ( m_isDebugRender )
	{
		g_pD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	}
}


