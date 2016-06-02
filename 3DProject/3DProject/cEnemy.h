#pragma once

#include "cCollisionObject.h"

class cBoundingSphere;
class cBody;

class cEnemy :
	public cCollisionObject
{
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Update() override;
	virtual void Render() override;

	virtual cBoundingSphere* GetBound() { return m_pBound; }
	virtual int GetCurrentHp() { return m_nCurrentHp; }
	virtual int GetMaxHp() { return m_nMaxHp; }
	virtual D3DXMATRIXA16 GetWorld() { return m_matWorld; }

	virtual void SetBound(cBoundingSphere* bound) { m_pBound = bound; }
	virtual void SetCurrentHp(int currHp) { m_nCurrentHp = currHp; }
	virtual void SetWorld(D3DXMATRIXA16* world) { m_matWorld = *world; }

protected:
	cBoundingSphere*		m_pBound;		//몬스터 바운딩박스
	cBody*					m_pBody;		//몬스터 바디

	int						m_nMaxHp;		//몬스터의 최대 피
	int						m_nCurrentHp;	//현재몬스터의 피
		
	D3DXMATRIXA16			m_matWorld;		//몬스터 월드 매트릭스
};

