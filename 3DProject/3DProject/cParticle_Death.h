#pragma once

#include "cParticle_Base.h"

class cParticle_Death
	: public cParticle_Base
{
	D3DXVECTOR3 m_vPosition;
public:
	cParticle_Death();
	virtual ~cParticle_Death();

	void SetParticle(D3DXVECTOR3 vPos);
	void Update() override;
	void ResetParticle(ParticleAttribute& attribute) override;

};

