#include "stdafx.h"
#include "cRandomUtil.h"

#include <stdlib.h>
#include <time.h>

cRandomUtil::cRandomUtil()
{
}


cRandomUtil::~cRandomUtil()
{
}

void cRandomUtil::Setup()
{
	srand((unsigned int)time(nullptr));
}

int cRandomUtil::GetInteger(int max, int min)
{
	return min + (rand() % (max - min + 1));
}

float cRandomUtil::GetFloat(float max, float min )
{
	return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

void cRandomUtil::GetVector(D3DXVECTOR3& out, D3DXVECTOR3& max, D3DXVECTOR3& min)
{
	out.x = GetFloat(max.x, min.x);
	out.y = GetFloat(max.y, min.y);
	out.z = GetFloat(max.z, min.z);
}