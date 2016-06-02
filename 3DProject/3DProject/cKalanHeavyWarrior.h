#pragma once

#include "cEnemy.h"

class cBody;
class cKalanHeavyWarrior :
	public cEnemy
{
public:
	cKalanHeavyWarrior();
	virtual ~cKalanHeavyWarrior();

	virtual void Update();
	virtual void Render();
};

