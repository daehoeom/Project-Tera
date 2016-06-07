#pragma once
#include "cCollisionObject.h"

#define TUMBLINGRANGE 150.f



class cTail;
class cBody;
class cHair;
class cFace;
class cWeaponMesh;

class cPlayer : 
	public cCollisionObject
{
public:
	cPlayer( );
	virtual ~cPlayer( );

	virtual void Update( ) override;
	virtual void Render( ) override;
	virtual void OnCollisionStay(cCollisionObject* rhs) override;

	void SetUpdateState();	//상태에 따라 업데이트를 다르게 진행
	void SetRenderState();	//상태에 따라 렌더를 다르게 진행
	void SetFSMState();
	void KeyControl();
	void SetAniTrack(int nIndex);

private:
	cBody*			m_pBody;
	cHair*			m_pHair;
	cFace*			m_pFace;
	cTail*			m_pTail;
	cWeaponMesh*	m_pHand;

	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3		m_vDirection;

	float			m_fSpeed;
	float			m_fAngle;
	float			m_fPassTime;
	float			m_fPeriod;

	bool			m_bIsAction;
	bool			m_bAlive;
	bool			m_bPushBehind;
	int				n;
};
