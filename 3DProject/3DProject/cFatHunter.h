#pragma once

#include "cEnemy.h"

class cBody;
class cFatHunter :
	public cEnemy
{
public:
	cFatHunter();
	virtual ~cFatHunter();

	virtual void Update();
	virtual void Render();
};

