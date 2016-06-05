#include "stdafx.h"
#include "cPlayer.h"
#include "cBody.h"
#include "cHair.h"
#include "cFace.h"
#include "cBoundingSphere.h"

cPlayer::cPlayer( ) :
	cCollisionObject( "Player" )
	, m_vDirection(D3DXVECTOR3(0, 0, 1))
	, m_fSpeed(1.f)
	, m_fAngle(0.f)
	, m_sState(ePlayerState::PLAYER_IDLE)
{
	//´ë±â»óÅÂ
	m_pIdleBody = new cBody;
	m_pIdleBody->Setup("CH/¿¤¸°", "¿¤¸°_¸ö_´ë±â.X");

	m_pIdleFace = new cFace;
	m_pIdleFace->SetNeckTM(&m_pIdleBody->GetNeckTM());
	m_pIdleFace->Setup("CH/¿¤¸°", "¿¤¸°_¾ó±¼_´ë±â.X");

	m_pIdleHair = new cHair;
	m_pIdleHair->SetHairTM(&m_pIdleFace->GetHairTM());
	m_pIdleHair->Setup("CH/¿¤¸°", "¿¤¸°_Çì¾î_´ë±â.X");

	//°ø°İ»óÅÂ
	m_pAttackBody = new cBody;
	m_pAttackBody->Setup("CH/¿¤¸°", "¿¤¸°_¸ö_°ø°İ.X");

	m_pAttackFace = new cFace;
	m_pAttackFace->SetNeckTM(&m_pAttackBody->GetNeckTM());
	m_pAttackFace->Setup("CH/¿¤¸°", "¿¤¸°_¾ó±¼_°ø°İ.X");

	m_pAttackHair = new cHair;
	m_pAttackHair->SetHairTM(&m_pAttackBody->GetHairTM());
	m_pAttackHair->Setup("CH/¿¤¸°", "¿¤¸°_Çì¾î_°ø°İ.X");

	//´Ş¸®±â»óÅÂ
	m_pRunBody = new cBody;
	m_pRunBody->Setup("CH/¿¤¸°", "¿¤¸°_¸ö_´Ş¸®±â.X");

	m_pRunFace = new cFace;
	m_pRunFace->SetNeckTM(&m_pRunBody->GetNeckTM());
	m_pRunFace->Setup("CH/¿¤¸°", "¿¤¸°_¾ó±¼_´Ş¸®±â.X");

	m_pRunHair = new cHair;
	m_pRunHair->SetHairTM(&m_pRunBody->GetHairTM());
	m_pRunHair->Setup("CH/¿¤¸°", "¿¤¸°_Çì¾î_´Ş¸®±â.X");

	D3DXMatrixIdentity(&m_matWorld);


	this->SetCollider(new cBoundingSphere(D3DXVECTOR3(0, 0, 0), 9.f));

	D3DXMATRIXA16 matLocal;
	D3DXMatrixTranslation(&matLocal, 0, 15, 0);
	this->GetColliderRepo()[0]->SetLocal(&matLocal);
}

cPlayer::~cPlayer( )
{
	SAFE_DELETE( m_pIdleBody );
	SAFE_DELETE( m_pIdleFace );
	SAFE_DELETE( m_pIdleHair );

	SAFE_DELETE( m_pAttackBody );
	SAFE_DELETE( m_pAttackFace );
	SAFE_DELETE( m_pAttackHair );

	SAFE_DELETE( m_pRunBody );
	SAFE_DELETE( m_pRunFace );
	SAFE_DELETE( m_pRunHair );
}

void cPlayer::Update( )
{
	__super::Update( );

	SetUpdateState();

	this->GetColliderRepo()[0]->SetWorld(&m_matWorld);

	KeyControl();
}

void cPlayer::Render( )
{
	__super::Render( );

	SetRenderState();
}

void cPlayer::KeyControl()
{
	D3DXMATRIXA16 matR, matT;

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_fAngle -= 0.1f;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_fAngle += 0.1f;
	}

	m_vDirection = D3DXVECTOR3(0, 0, -1);
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_sState = ePlayerState::PLAYER_RUN;
		SetPosition(GetPosition() + m_vDirection * m_fSpeed);
	}

	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		m_sState = ePlayerState::PLAYER_IDLE;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_sState = ePlayerState::PLAYER_RUN;
		SetPosition(GetPosition() - m_vDirection * m_fSpeed);
	}

	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		m_sState = ePlayerState::PLAYER_IDLE;
	}

	D3DXMatrixTranslation(&matT, GetPosition().x, GetPosition().y, GetPosition().z);
	m_matWorld = matR * matT;
}

void cPlayer::SetUpdateState( )
{
	switch (m_sState)
	{
	case ePlayerState::PLAYER_IDLE :
		if ( m_pIdleBody )
		{
			m_pIdleBody->Update( );
			m_pIdleBody->SetWorld(&m_matWorld);
		}
		if (m_pIdleHair)
		{
			m_pIdleHair->SetHairTM(
				&m_pIdleBody->GetHairTM( ));
			m_pIdleHair->Update( );
		}
		if (m_pIdleFace)
		{
			m_pIdleFace->SetNeckTM(
				&m_pIdleBody->GetNeckTM( ));
			m_pIdleFace->Update( );
		}
		break;

	case ePlayerState::PLAYER_ATTACK:
		if ( m_pAttackBody )
		{
			m_pAttackBody->Update( );
			m_pAttackBody->SetWorld(&m_matWorld);
		}
		if (m_pAttackHair)
		{
			m_pAttackHair->SetHairTM(
				&m_pAttackBody->GetHairTM( ));
			m_pAttackHair->Update( );
		}
		if ( m_pAttackFace )
		{
			m_pAttackFace->SetNeckTM( &m_pAttackBody->GetNeckTM( ));
			m_pAttackFace->Update( );
		}

		break;

	case ePlayerState::PLAYER_RUN:
		if ( m_pRunBody )
		{
			m_pRunBody->Update( );
			m_pRunBody->SetWorld(&m_matWorld);
		}
		if ( m_pRunHair )
		{
			m_pRunHair->SetHairTM( &m_pRunBody->GetHairTM( ));
			m_pRunHair->Update( );
		}
		if ( m_pRunFace )
		{
			m_pRunFace->SetNeckTM(&m_pRunBody->GetNeckTM());
			m_pRunFace->Update( );
		}

		break;
	}
}

void cPlayer::SetRenderState()
{
	switch (m_sState)
	{
	case ePlayerState::PLAYER_IDLE:
		if (m_pIdleBody)
		{
			m_pIdleBody->Render();
		}
		if (m_pIdleHair)
		{
			m_pIdleHair->Render();
		}
		if (m_pIdleFace)
		{
			m_pIdleFace->Render();
		}

		break;

	case ePlayerState::PLAYER_ATTACK:
		if (m_pAttackBody)
		{
			m_pAttackBody->Render();
		}
		if (m_pAttackHair)
		{
			m_pAttackHair->Render();
		}
		if (m_pAttackFace)
		{
			m_pAttackFace->Render();
		}

		break;

	case ePlayerState::PLAYER_RUN:
		if (m_pRunBody)
		{
			m_pRunBody->Render();
		}
		if (m_pRunHair)
		{
			m_pRunHair->Render();
		}
		if (m_pRunFace)
		{
			m_pRunFace->Render();
		}
		break;
	}
}
