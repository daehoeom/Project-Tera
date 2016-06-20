#pragma once
#include "cGameObject.h"

class cSprite :
	public cGameObject
{
public:
	explicit cSprite( const char* spritePath );
	virtual ~cSprite( );

	void Load( const char* spritePath );
	void Update( );
	void Render( );

	const D3DXIMAGE_INFO& GetImgInfo( ) const
	{
		return m_imgInfo;
	}

private:
	LPDIRECT3DTEXTURE9 m_texture = nullptr;
	D3DXIMAGE_INFO m_imgInfo;
	RECT m_rtDrawArea;
};

