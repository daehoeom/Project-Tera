#include "stdafx.h"
#include "cSprite.h"

#include "cDeviceManager.h"

cSprite::cSprite( const char* spritePath ) :
	m_texture( nullptr )
{
	this->Load( spritePath );
}

void cSprite::Load( const char* spritePath )
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
		MessageBox( GetFocus( ), "Failed to invoke D3DXCreateTextureFromFileEx.",
			"WARNING!", MB_OK );
		return;
	}
}


cSprite::~cSprite( )
{
	SAFE_RELEASE( m_texture );
}

void cSprite::Update( )
{
}

void cSprite::Render( )
{
	RECT rc;
	SetRect( &rc, 0, 0, m_imgInfo.Width, m_imgInfo.Height );

	g_pD3DSprite->SetTransform( &this->GetWorld( ));
	g_pD3DSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );

	g_pD3DSprite->Draw( m_texture,
		&rc,
		&D3DXVECTOR3( 0, 0, 0 ),
		&D3DXVECTOR3( 0, 0, 0 ),
		D3DCOLOR_XRGB( 255, 255, 255 ) );

	g_pD3DSprite->End( );
}
