#include "stdafx.h"
#include "IRenderable.h"


IRenderable::IRenderable( 
	const std::wstring& objName ) :

	cGameObject( objName ),
	m_texture( nullptr ),
	m_vb( nullptr ),
	m_ib( nullptr )
{
	D3DXMatrixIdentity( &m_matWorld );
}

IRenderable::~IRenderable( )
{
	SAFE_RELEASE( m_vb );
	SAFE_RELEASE( m_ib );
	SAFE_RELEASE( m_texture );
}

void IRenderable::Update( )
{
	__super::Update( );
}

void IRenderable::SetVertexBuffer( IDirect3DVertexBuffer9* vertexBuffer )
{
	m_vb = vertexBuffer;
}

IDirect3DVertexBuffer9* IRenderable::GetVertexBuffer( )
{
	return m_vb;
}

void IRenderable::SetIndexBuffer( IDirect3DIndexBuffer9* indexBuffer )
{
	m_ib = indexBuffer;
}

void IRenderable::AddTexture( IDirect3DTexture9 * texture )
{
	m_texture = texture;
}

void IRenderable::SetMaterial( const D3DMATERIAL9 & material )
{
	m_material = material;
}

IDirect3DIndexBuffer9* IRenderable::GetIndexBuffer( )
{
	return m_ib;
}

IDirect3DTexture9* IRenderable::GetTexture( int index ) const
{
	return m_texture;
}

const D3DMATERIAL9 & IRenderable::GetMaterial( ) const
{
	return m_material;
}
