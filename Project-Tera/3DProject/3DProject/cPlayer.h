#pragma once
#include "cCollisionObject.h"

class cBody;
class cHair;
class cFace;

class cPlayer : 
	public cCollisionObject
{
public:
	cPlayer( );
	virtual ~cPlayer( );

	virtual void Update( ) override;
	virtual void Render( ) override;

private:
	std::shared_ptr<cBody>	m_pIdleBody;
	std::shared_ptr<cHair>	m_pIdleHair;
	std::shared_ptr<cFace>	m_pIdleFace;

	std::shared_ptr<cBody>	m_pAttackBody;
	std::shared_ptr<cHair>	m_pAttackHair;
	std::shared_ptr<cFace>	m_pAttackFace;

	std::shared_ptr<cBody>	m_pRunBody;
	std::shared_ptr<cHair>	m_pRunHair;
	std::shared_ptr<cFace>	m_pRunFace;
};