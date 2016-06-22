#include "stdafx.h"
#include "cParticle_Death.h"


cParticle_Death::cParticle_Death()
	:m_vPosition({ 0, 0, 0 })
{
}

cParticle_Death::~cParticle_Death()
{
}

void cParticle_Death::SetParticle(D3DXVECTOR3 vPos)
{
	m_vPosition = vPos;

	m_fSize = 10.f;

	for (int i = 0; i < 3000; i++)
	{
		AddParticle();
	}
}

void cParticle_Death::Update()
{
	for (auto iter = m_lParticles.begin(); iter != m_lParticles.end(); ++iter)
	{
		iter->pos += (iter->velocity * (float)g_pTimeManager->GetDeltaTime());

		// 바운딩 박스 밖을 벗어나면 리셋(눈은 계속 내려야 하니까)
		iter->age += g_pTimeManager->GetDeltaTime();

		if (iter->age > iter->lifeTime)
		{
			iter->isAlive = false;
		}
	}
}

void cParticle_Death::ResetParticle(ParticleAttribute& attribute)
{
	attribute.isAlive = true;

	/*attribute.pos.x = cRandomUtil::GetFloat(m_vPosition.x + 30.f, m_vPosition.x - 30.f);
	attribute.pos.z = cRandomUtil::GetFloat(m_vPosition.z + 30.f, m_vPosition.z - 30.f);*/
	attribute.pos.x = m_vPosition.x;
	attribute.pos.z = m_vPosition.z;

	attribute.pos.y = m_vPosition.y + 20;

	attribute.velocity.x = cRandomUtil::GetFloat(1.0f, -1.f) * cRandomUtil::GetFloat(10.f, 2.7f);
	attribute.velocity.y = 0;
	attribute.velocity.z = cRandomUtil::GetFloat(1.0f, -1.f) * cRandomUtil::GetFloat(10.f, 2.7f);

	attribute.age = 0.f;
	attribute.lifeTime = cRandomUtil::GetFloat(4.f);

	attribute.color = D3DCOLOR_XRGB(255, 0, 0);
}