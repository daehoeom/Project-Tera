#pragma once
#include "cGameObject.h"


class IRenderable : 
	public cGameObject
{
public:
	IRenderable( const std::wstring& objName );
	virtual ~IRenderable( ) = 0;


public:
	// Sets
	void SetModelPath( const std::string& modelPath );
	void SetVertexBuffer( _In_ IDirect3DVertexBuffer9* vertexBuffer );
	void SetIndexBuffer( _In_ IDirect3DIndexBuffer9* indexBuffer );
	void AddTexture( _In_ IDirect3DTexture9* texture );
	void SetMaterial( const D3DMATERIAL9& material );

	// Gets
	const std::string& GetModelPath( ) const;
	IDirect3DVertexBuffer9* GetVertexBuffer( );
	IDirect3DIndexBuffer9* GetIndexBuffer( );
	IDirect3DTexture9* GetTexture( int index = 0 ) const;
	const D3DMATERIAL9& GetMaterial( ) const;

private:
	std::string m_modelPath;
	D3DXMATRIXA16 m_matWorld;
	IDirect3DVertexBuffer9* m_vb;
	IDirect3DIndexBuffer9* m_ib;
	IDirect3DTexture9* m_texture;
	D3DMATERIAL9 m_material;
};

