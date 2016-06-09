#pragma once
class IScene
{
public:
	IScene( );
	virtual ~IScene( ) = 0;

	virtual void Render( ) = 0;
	virtual void Update( ) = 0;
};

