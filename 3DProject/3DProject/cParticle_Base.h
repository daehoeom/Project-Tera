#pragma once

#include "Particle.h"

class cParticle_Base
{
protected:
	D3DXMATRIXA16						m_matWorld;			
	float								m_fSize;			//파티클 크기
	LPDIRECT3DTEXTURE9					m_pTexture;			//파티클 텍스처
	LPDIRECT3DVERTEXBUFFER9				m_pVertexBuffer;	//파티클 버텍스 버퍼
	std::list<ParticleAttribute>		m_lParticles;		//전체 파티클 리스트

	//아래 3개는 파티클을 좀 더 효율적으로 그리기 위한 변수
	DWORD								m_dwVbSize;			//버텍스 버퍼 크기
	DWORD								m_dwVbOffset;		//버텍스 버퍼를 잠그기 위한 offset(파티클 갯수 단위)
	DWORD								m_dwVbBatchSize;	//하나의 단계에 들어갈 파티클의 갯수

	virtual void PreRender();
	virtual void PostRender();
	DWORD FloatToDword(float f) { return *((DWORD*)(&f)); }

public:
	cParticle_Base();
	virtual ~cParticle_Base();

	void Setup(char* szFullPath);
	virtual void Update() = 0;
	void Render();

	virtual void AddParticle();		//파티클 하나 추가

	virtual void Reset();			//파티클 재사용용
	virtual void ResetParticle(ParticleAttribute& attribute) = 0;		//파티클 타입에 맞게 리셋하기 위한 것

	bool IsEmpty();		//파티클이 비어있음
	bool IsDead();		//파티클이 다 죽음
};

