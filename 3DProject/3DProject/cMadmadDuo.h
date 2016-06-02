#pragma once

#include "cEnemy.h"

class cBody;
class cMadmadDuo :
	public cEnemy
{
public:
	cMadmadDuo();
	virtual ~cMadmadDuo();

	virtual void Update();
	virtual void Render();
};

