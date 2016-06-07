#pragma once

class ICollider
{
public:
	ICollider( ) {}
	virtual ~ICollider( ) {}

#ifdef _DEBUG
	virtual void Render( ) = 0;
#endif
};