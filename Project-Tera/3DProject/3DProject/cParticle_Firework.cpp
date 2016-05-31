#include "stdafx.h"
#include "cParticle_Firework.h"


cParticle_Firework::cParticle_Firework(D3DXVECTOR3& _origin, int numParticles)
	: m_vOrigin(_origin)
	, m_fRadius(100.f)
	, m_fBombTime(2.f)
{
	m_fSize = 0.9f;

	for (int i = 0; i < numParticles; i++)
	{
		AddParticle();
	}
}


cParticle_Firework::~cParticle_Firework()
{
}

void cParticle_Firework::Update()
{
	for (auto iter = m_lParticles.begin(); iter != m_lParticles.end(); ++iter)
	{
		if (iter->isAlive)
		{
			iter->pos += (iter->velocity * g_pTimeManager->GetDeltaTime());
			iter->age += g_pTimeManager->GetDeltaTime();
			if (iter->age > iter->lifeTime)
			{
				iter->isAlive = false;
			}
		}
	}

	if (IsDead())
	{
		Reset();
	}
}

void cParticle_Firework::ResetParticle(ParticleAttribute& attribute)
{
	attribute.isAlive = true;
	attribute.pos = m_vOrigin;

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	cRandomUtil::GetVector(attribute.velocity, min, max);
	D3DXVec3Normalize(&attribute.velocity, &attribute.velocity);

	attribute.velocity *= m_fRadius;

	attribute.age = 0.0f;

	attribute.color = D3DXCOLOR(cRandomUtil::GetFloat(1.0f),
		cRandomUtil::GetFloat(1.0f),
		cRandomUtil::GetFloat(1.0f),
		1.0f);

	attribute.lifeTime = m_fBombTime;

}

void cParticle_Firework::PreRender()
{
	cParticle_Base::PreRender();

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//z-buffer 읽기만 하고 쓰기는 금지
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void cParticle_Firework::PostRender()
{
	cParticle_Base::PostRender();

	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
