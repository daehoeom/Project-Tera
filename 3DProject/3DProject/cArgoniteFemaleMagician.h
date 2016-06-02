#pragma once

#include "cEnemy.h"

class cBody;
class cArgoniteFemaleMagician :
	public cEnemy
{
public:
	cArgoniteFemaleMagician();
	~cArgoniteFemaleMagician();

	virtual void Update();
	virtual void Render();
};

