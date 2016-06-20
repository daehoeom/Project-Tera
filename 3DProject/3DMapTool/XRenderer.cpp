#include "stdafx.h"
#include "XRenderer.h"

#include "cDeviceManager.h"
#include "IRenderable.h"

cXRenderer::cXRenderer( 
	const char* xFilePath )
{
	if ( FAILED( D3DXLoadMeshFromXA( xFilePath, D3DXMESH_SYSTEMMEM, 
			g_pD3DDevice, NULL, NULL, NULL, &m_mtrlCount, &m_mesh )))
	{
		MessageBox( GetFocus( ),
			L"Failed to invoke D3DXLoadMeshFromXA.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION 
		);
	};

	this->SetupMinAndMax( );
}

cXRenderer::~cXRenderer( )
{
	SAFE_RELEASE( m_mesh );
}

void cXRenderer::Render( )
{
	assert( this->GetOwner( ) );

	g_pD3DDevice->SetTransform( D3DTS_WORLD,
		&this->GetOwner( )->GetWorld( ) );

	if ( m_mesh )
	{
		for ( int i = 0; i < m_mtrlCount; ++i )
		{
			m_mesh->DrawSubset( i );
		}
	}
}

void cXRenderer::SetupMinAndMax( )
{
	assert( m_mesh );

	BYTE* pVertices = nullptr;
	m_mesh->LockVertexBuffer( D3DLOCK_READONLY, ( LPVOID* )&pVertices );

	D3DXComputeBoundingBox( ( D3DXVECTOR3* )pVertices,
		m_mesh->GetNumVertices( ), D3DXGetFVFVertexSize( m_mesh->GetFVF( ) ),
		&m_min, &m_max );

	m_mesh->UnlockVertexBuffer( );
}
