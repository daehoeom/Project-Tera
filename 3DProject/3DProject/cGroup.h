#pragma once

#include "cMtlTex.h"

class cGroup
{
protected:
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_PASS_BY_REF(SpMtlTex, m_pMtlTex, MtlTex);

public:
	cGroup(void);
	~cGroup(void);

	void Render();
};

