#pragma once
#include "cCollisionObject.h"

class cUnitObject :
	public cCollisionObject
{
public:
	cUnitObject( );
	virtual ~cUnitObject( );

	//Hp
	int GetMaxHp( ) { return m_nMaxHp; }

	void SetCurrHp( int hp ) { m_nCurrHp = hp; }
	int GetCurrHp( ) { return m_nCurrHp; }
	
	void SetCollision(bool isCollision) { m_bCollision = isCollision; }
	bool GetCollision() { return m_bCollision; }

	//State
	void SetDead( bool isDead );
	bool IsDead( );
	
private:
	bool m_isDead;
	int m_nMaxHp;
	int m_nCurrHp;
	bool m_bCollision;
};

inline void cUnitObject::SetDead( bool isDead )
{
	m_isDead = isDead;
}

inline bool cUnitObject::IsDead( )
{
	return m_isDead;
}

