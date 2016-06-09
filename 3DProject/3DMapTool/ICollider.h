#pragma once

class ICollider
{
public:
	ICollider( ) {}
	virtual ~ICollider( ) {}

	virtual void Update( ) = 0;
	virtual void Render( const D3DXMATRIXA16& ) = 0;
};