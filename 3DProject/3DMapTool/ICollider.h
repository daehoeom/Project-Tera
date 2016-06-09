#pragma once

class ICollider
{
public:
	ICollider( ) {}
	virtual ~ICollider( ) {}

	virtual void Update( const D3DXMATRIXA16& TM ) = 0;
	virtual void Render( ) = 0;
};