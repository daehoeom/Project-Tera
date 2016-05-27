#pragma once
#include "cParticle_Base.h"

class cParticle_Firework :
	public cParticle_Base

{
protected:
	D3DXVECTOR3				m_vOrigin;
	float					m_fRadius;
	float					m_fBombTime;

	void PreRender() override;
	void PostRender() override;

public:
	cParticle_Firework(D3DXVECTOR3& _origin, int numParticles);
	virtual ~cParticle_Firework();

	void Update() override;
	void ResetParticle(ParticleAttribute& attribute) override;
};

