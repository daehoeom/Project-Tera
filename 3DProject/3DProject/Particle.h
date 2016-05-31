#pragma once

struct Particle
{
	D3DXVECTOR3		pos;		//파티클이 나오는 곳
	D3DCOLOR		color;		//파티클 색상

	Particle() 
		:pos(0, 0, 0), color(D3DCOLOR_XRGB(0, 0, 0))
	{
	}

	Particle(D3DXVECTOR3 _pos, D3DCOLOR _color)
		:pos(_pos), color(_color)
	{
	}

	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
};


struct ParticleAttribute
{
	D3DXVECTOR3		pos;		//파티클 위치
	D3DXVECTOR3		velocity;	//가중치
	float			lifeTime;	//파티클 생명시간
	float			age;		//파티클의 나이
	D3DXCOLOR		color;		//파티클 색상
	bool			isAlive;	//파티클의 존재여부

	ParticleAttribute()
		: pos(0, 0, 0)
		, velocity(0, 0, 0)
		, lifeTime(0.f)
		, age(0.f)
		, color(D3DCOLOR_XRGB(255, 255, 255))
		, isAlive(false)
	{
	}
};