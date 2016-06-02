#pragma once

#include "cEnemy.h"

class cBody;
class cPixie :
	public cEnemy

{
public:
	cPixie();
	virtual ~cPixie();

	virtual void Update();
	virtual void Render();
};


