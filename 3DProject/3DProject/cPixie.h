#pragma once

#include "cEnemy.h"

class cEnemySkinMesh;
class cPixie :
	public cEnemy

{
public:
	cPixie();
	virtual ~cPixie();

	virtual void Update();
	virtual void Render();
};


