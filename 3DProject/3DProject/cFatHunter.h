#pragma once

#include "cEnemy.h"

class cEnemySkinMesh;
class cFatHunter :
	public cEnemy
{
public:
	cFatHunter();
	virtual ~cFatHunter();

	virtual void Update();
	virtual void Render();
};

