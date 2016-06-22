#pragma once
#include "cUnitObject.h"
#include "cCommandCombo.h"

#define TUMBLINGRANGE 150.f

class cSkinnedMesh;
class cPlayerWeapon;

enum ePlayerState
{
	PLAYER_BATTLEIDLE = 5,
	PLAYER_RUN = 46,
	PLAYER_TUMBLING = 6,
	PLAYER_SKILL1 = 26,			//강하게 내려찍기
	PLAYER_SKILL2 = 0,			//슬래쉬
	PLAYER_SKILL3 = 27,			//강하게 옆으로 찍기
	PLAYER_SKILL4 = 28,			//회오리치기
	PLAYER_COMBO1 = 2,			//플레이어 콤보1
	PLAYER_COMBO2 = 4,			//플레이어 콤보2
	PLAYER_COMBO3 = 8,			//플레이어 콤보3
	PLAYER_COMBO4 = 17,			//플레이어 콤보4
	PLAYER_DEATH = 25,			//플레이어 데스
	PLAYER_DEATHWAIT = 24,		//플레이어 데스웨잇
};

class cPlayer : 
	public cUnitObject
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
	void SetPlayerState( ePlayerState p );
	ePlayerState GetPlayerState( );

	void SetUpdateState();	//상태에 따라 업데이트를 다르게 진행
	void SetRenderState();	//상태에 따라 렌더를 다르게 진행
	void SetFSMState();
	void KeyControl();
	void SetAniTrack(int nIndex);

private:
	ePlayerState	m_sPState;
	
	std::vector<cSkinnedMesh*> m_vecSkinnedMesh;
	cPlayerWeapon*	m_playerWeapon;

	cCommandCombo*	m_pCombo;

	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3		m_vDirection;
	
	//물체 그림자

	float			m_fSpeed;
	float			m_fPassTime;
	float			m_fPeriod;

	bool			m_bIsAction;
	bool			m_bAlive;
	bool			m_bPushBehind;
	float			n;
};

inline void cPlayer::SetPlayerState(ePlayerState p)
{
	m_sPState = p;
}

inline ePlayerState cPlayer::GetPlayerState()
{
	return m_sPState;
}