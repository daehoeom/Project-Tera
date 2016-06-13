#pragma once
#include "cCollisionObject.h"
#include "cCommandCombo.h"

#define TUMBLINGRANGE 150.f

class cTail;
class cBody;
class cHair;
class cFace;
class cWeaponMesh;
class cPlayerWeapon;

class cPlayer : 
	public cCollisionObject
{
public:
	cPlayer( );
	virtual ~cPlayer( );

	virtual void Update( ) override;
	virtual void Render( ) override;

public:
	virtual void OnCollisionEnter( int colliderIndex, cCollisionObject* rhs ) override;
	virtual void OnCollisionStay( int colliderIndex, cCollisionObject* rhs ) override;
	virtual void OnCollisionEnd( int colliderIndex, cCollisionObject* rhs ) override;

public:
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
	cPlayerWeapon*	m_playerWeapon;
	cCommandCombo*	m_pCombo;

	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3		m_vDirection;
	
	//물체 그림자
	LPD3DXEFFECT	m_pEffect;

	//그림자맵 렌더타깃
	LPDIRECT3DTEXTURE9 m_pRenderTarget;
	LPDIRECT3DSURFACE9 m_pDepthStencil;

	float			m_fSpeed;
	float			m_fPassTime;
	float			m_fPeriod;

	bool			m_bIsAction;
	bool			m_bAlive;
	bool			m_bPushBehind;
	float			n;
};
