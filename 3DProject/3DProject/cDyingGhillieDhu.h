#pragma once

#include "cEnemy.h"

class cEnemySkinMesh;
class cDyingGhillieDhu:
	public cEnemy
{
public:
	cDyingGhillieDhu();
	virtual ~cDyingGhillieDhu();
 
	virtual void Update();
	virtual void Render();
};

