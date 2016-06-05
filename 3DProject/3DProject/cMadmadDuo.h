#pragma once

#include "cEnemy.h"

class cEnemySkinMesh;
class cMadmadDuo :
	public cEnemy
{
	int n = 0;
public:
	cMadmadDuo();
	virtual ~cMadmadDuo();

	virtual void Update();
	virtual void Render();
};

