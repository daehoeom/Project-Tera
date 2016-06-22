#pragma once
#include "cGameObject.h"

class c3DSprite :
	public cGameObject
{
public:
	explicit c3DSprite( const char* spritePath );
	virtual ~c3DSprite( );

	virtual void Render( ) override;
	virtual void Update( ) override;

public:
	IDirect3DVertexBuffer9* GetVertexBuffer( );
	IDirect3DIndexBuffer9* GetIndexBuffer( );
	LPDIRECT3DTEXTURE9 GetTexture( );

private:
	void Load( const char* spritePath );
	void SetupVertices( );
	void SetupIndices( );

private:
	IDirect3DVertexBuffer9* m_vb;
	IDirect3DIndexBuffer9* m_ib;

	LPDIRECT3DTEXTURE9 m_texture = nullptr;
	D3DXIMAGE_INFO m_imgInfo;
	RECT m_rtDrawArea;
};

inline IDirect3DVertexBuffer9* c3DSprite::GetVertexBuffer( )
{
	return m_vb;
}

inline IDirect3DIndexBuffer9* c3DSprite::GetIndexBuffer( )
{
	return m_ib;
}

inline LPDIRECT3DTEXTURE9 c3DSprite::GetTexture( )
{
	return m_texture;
}

class cBuilboard3DSprite :
	public c3DSprite
{
public:
	explicit cBuilboard3DSprite( const char* spritePath );
	virtual ~cBuilboard3DSprite( );

	virtual void Render( ) override;
};

