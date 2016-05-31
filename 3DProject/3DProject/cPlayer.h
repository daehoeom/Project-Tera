#pragma once
#include "GameObject.h"

class cPlayer : 
	public cGameObject
{
	std::shared_ptr<class cBody>	m_pIdleBody;
	std::shared_ptr<class cHair>	m_pIdleHair;
	std::shared_ptr<class cFace>	m_pIdleFace;

	std::shared_ptr<class cBody>	m_pAttackBody;
	std::shared_ptr<class cHair>	m_pAttackHair;
	std::shared_ptr<class cFace>	m_pAttackFace;

	std::shared_ptr<class cBody>	m_pRunBody;
	std::shared_ptr<class cHair>	m_pRunHair;
	std::shared_ptr<class cFace>	m_pRunFace;

	PlayerState						m_sState;

public:
	cPlayer( );
	virtual ~cPlayer( );

	virtual void Update( );
	virtual void Render( );
	void SetChangeState();
	void StateUpdate();
	void StateRender();
	void KeyControl();
};