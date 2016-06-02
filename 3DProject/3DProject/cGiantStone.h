#pragma once

#include "cEnemy.h"

class cBody;
class cGiantStone :
	public cEnemy
{
public:
	cGiantStone();
	virtual~cGiantStone();

	virtual void Update();
	virtual void Render();
};

