#include "stdafx.h"
#include "cParticle_Firework.h"


cParticle_Firework::cParticle_Firework(D3DXVECTOR3& _origin, int numParticles)
{
	/*origin = _origin;
	size = 0.9f;

	for (int i = 0; i < numParticles; i++)
	{
		AddParticle();
	}*/
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
	attribute.pos = origin;

	/*D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	RandomUtil::GetVector(attribute.velocity, min, max);
	D3DXVec3Normalize(&attribute.velocity, &attribute.velocity);

	attribute.velocity *= radius;

	attribute.age = 0.0f;

	attribute.color = D3DXCOLOR(RandomUtil::GetFloat(1.0f),
		RandomUtil::GetFloat(1.0f),
		RandomUtil::GetFloat(1.0f),
		1.0f);

	attribute.lifeTime = bombTime;*/

}

void cParticle_Firework::PreRender()
{
	//Particle_Base::PreRender();

	//GameManager::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//GameManager::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	////z-buffer 읽기만 하고 쓰기는 금지
	//GameManager::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void cParticle_Firework::PostRender()
{
	/*Particle_Base::PostRender();

	GameManager::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, true);*/
}
