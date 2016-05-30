#pragma once
#include "GameObject.h"

class cPlayer :
	public GameObject
{
public:
	cPlayer( );
	virtual ~cPlayer( );

	virtual void Update( ) override;
	virtual void Render( ) override;

private:
};

