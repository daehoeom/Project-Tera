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

	void SetUpdateState();	//상태에 따라 업데이트를 다르게 진행
	void SetRenderState();	//상태에 따라 렌더를 다르게 진행
	void KeyControl();

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
