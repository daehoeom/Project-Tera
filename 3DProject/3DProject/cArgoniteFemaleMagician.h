#pragma once

#include "cEnemy.h"

class cEnemySkinMesh;
class cArgoniteFemaleMagician :
	public cEnemy
{
public:
	cArgoniteFemaleMagician();
	~cArgoniteFemaleMagician();

	virtual void Update();
	virtual void Render();
};

