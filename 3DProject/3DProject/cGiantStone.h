#pragma once

#include "cEnemy.h"

class cEnemySkinMesh;
class cGiantStone :
	public cEnemy
{
public:
	cGiantStone();
	virtual~cGiantStone();

	virtual void Update();
	virtual void Render();
};

