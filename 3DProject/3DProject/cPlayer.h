#pragma once
#include "GameObject.h"

class cPlayer : public GameObject
{
public:
	cPlayer( );
	virtual ~cPlayer( );

	virtual void Update( );
	virtual void Render( );
};