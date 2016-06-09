#pragma once
#include "IScene.h"


class TestScene :
	public IScene
{
public:
	TestScene( const std::string& xmlPath );
	virtual ~TestScene( );

	virtual void Render( ) override;
	virtual void Update( ) override;
};

