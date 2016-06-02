#pragma once

#include "cCollisionObject.h"
#include "cBoundingSphere.h"

class cBody;

class cEnemy :
	public cCollisionObject
{
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Update() override;
	virtual void Render() override;

	virtual int GetCurrentHp() { return m_nCurrentHp; }
	virtual int GetMaxHp() { return m_nMaxHp; }

	virtual void SetCurrentHp(int currHp) { m_nCurrentHp = currHp; }

protected:
	cBody*			m_pBody;		//몬스터 바디

	int	  			m_nMaxHp;		//몬스터의 최대 피
	int	  			m_nCurrentHp;	//현재몬스터의 피

	D3DXMATRIXA16	m_matWorld;	//몬스터의 월드매트릭스
};

