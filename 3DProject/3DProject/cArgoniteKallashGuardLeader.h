#pragma once

#include "cEnemy.h"

class cEnemySkinMesh;
class cArgoniteKallashGuardLeader :
	public cEnemy
{
public:
	cArgoniteKallashGuardLeader();
	virtual ~cArgoniteKallashGuardLeader();

	virtual void Update();
	virtual void Render();
};


