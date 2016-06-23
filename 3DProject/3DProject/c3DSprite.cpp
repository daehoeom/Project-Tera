#include "stdafx.h"
#include "c3DSprite.h"

#include "cCamera.h"
#include "cDeviceManager.h"
#include "cShaderManager.h"

c3DSprite::c3DSprite( 
	const char* spritePath )
{
	this->Load( spritePath );
}

c3DSprite::~c3DSprite( )
{
	SAFE_RELEASE( m_ib );
	SAFE_RELEASE( m_vb );
	SAFE_RELEASE( m_texture ); 
}

void c3DSprite::Render( )
{
	this->PrevRender( );

	g_pD3DDevice->SetTexture( 0, m_texture );
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &this->GetWorld( ));
	g_pD3DDevice->SetStreamSource( 0, m_vb, 0, sizeof( ST_PNT_VERTEX ));
	g_pD3DDevice->SetIndices( m_ib );
	g_pD3DDevice->SetFVF( ST_PNT_VERTEX::FVF );
	g_pD3DDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		4,
		0,
		2
	);

	this->PostRender( );
}

void c3DSprite::Update( )
{
}

void c3DSprite::PrevRender( )
{
	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	g_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
}

void c3DSprite::PostRender( )
{
	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	g_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
}

void c3DSprite::Load( 
	const char * spritePath )
{
	SAFE_RELEASE( m_texture );

	HRESULT hr = D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		spritePath,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_imgInfo,
		NULL,
		&m_texture
	);

	if ( FAILED( hr ) )
	{
		MessageBox(
			GetFocus( ),
			( std::string( "Failed to load texture. ( " ) + spritePath + std::string( ")" ) ).c_str( ),
			"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
	}

	this->SetupVertices( );
	this->SetupIndices( );
}

void c3DSprite::SetupVertices( )
{
	g_pD3DDevice->CreateVertexBuffer(
		sizeof( ST_PNT_VERTEX ) * 4,
		0,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_vb,
		nullptr
	);

	ST_PNT_VERTEX* vertices;
	m_vb->Lock( 0, 0, ( void** )&vertices, 0 );

	vertices[0] = {{ -1.f, -1.f, 0.f }, { 0.f, 0.f, -1.f }, { 0, 1 }};
	vertices[1] = {{ -1.f, 1.f, 0.f }, { 0.f, 0.f, -1.f }, { 0, 0 }};
	vertices[2] = {{ 1.f, 1.f, 0.f }, { 0.f, 0.f, -1.f }, { 1, 0 }};
	vertices[3] = {{ 1.f, -1.f, 0.f }, { 0.f, 0.f, -1.f },  { 1, 1 }};

	m_vb->Unlock( );
}

void c3DSprite::SetupIndices( )
{
	g_pD3DDevice->CreateIndexBuffer(
		sizeof( DWORD )* 6,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_ib,
		nullptr
	);

	DWORD* indices;
	m_ib->Lock( 0, 0, ( void** )&indices, 0 );

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	m_ib->Unlock( );

}

cBillboard3DSprite::cBillboard3DSprite( 
	const char * spritePath ) :
	c3DSprite( spritePath )
{
}

cBillboard3DSprite::~cBillboard3DSprite( )
{
}

void cBillboard3DSprite::Update( )
{
	m_matBillboard = cCamera::Get( )->GetView( );
	D3DXMatrixInverse( &m_matBillboard, nullptr, &m_matBillboard );
	m_matBillboard._41 = this->GetPosition( ).x;
	m_matBillboard._42 = this->GetPosition( ).y;
	m_matBillboard._43 = this->GetPosition( ).z;

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling( &matScale,
		this->GetScale( ).x,
		this->GetScale( ).y,
		this->GetScale( ).z );

	m_matBillboard = matScale * m_matBillboard;
}

void cBillboard3DSprite::Render( )
{
	this->PrevRender( );

	g_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	g_pD3DDevice->SetTexture( 0, this->GetTexture() );
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &m_matBillboard );
	g_pD3DDevice->SetStreamSource( 0, this->GetVertexBuffer( ), 0, sizeof( ST_PNT_VERTEX ));
	g_pD3DDevice->SetIndices( this->GetIndexBuffer( ) );
	g_pD3DDevice->SetFVF( ST_PNT_VERTEX::FVF );
	g_pD3DDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		4,
		0,
		2
	);

	this->PostRender( );
}
