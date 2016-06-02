#pragma once

#include "cEnemy.h"

class cBody;
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

