#pragma once

class ICollider
{
public:
	ICollider( ) {}
	virtual ~ICollider( ) {}

	virtual void Render( ) = 0;
};