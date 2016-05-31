#include "stdafx.h"
#include "cPlayer.h"
#include "cBody.h"
#include "cHair.h"
#include "cFace.h"
#include "cBoundingBox.h"
#include "cPlayerState.h"

cPlayer::cPlayer( ) :
	 cGameObject( "Player" )
	 , m_pIdleBody(nullptr)
	 , m_pIdleHair(nullptr)
	 , m_pIdleFace(nullptr)
	 , m_pAttackBody(nullptr)
	 , m_pAttackHair(nullptr)
	 , m_pAttackFace(nullptr)
	 , m_pRunBody(nullptr)
	 , m_pRunFace(nullptr)
	 , m_pRunHair(nullptr)
	 , m_sState(player_IDLE)
{
	this->AddState( eFSMState::kIdle, new cPlayerIdleState( this ));
	this->SetCollider( new cBoundingBox( this, D3DXVECTOR3( -1.f,-1.f,-1.f ), D3DXVECTOR3( 1.f, 1.f, 1.f )));

	this->TranslateState( eFSMState::kIdle );

	//´ë±â»óÅÂ
	m_pIdleBody.reset(new cBody);
	m_pIdleBody->Setup("./¿¤¸°", "¿¤¸°_¸ö_´ë±â.X");

	m_pIdleFace.reset(new cFace);
	m_pIdleFace->SetNeckTM(&m_pIdleBody->GetNeckTM());
	m_pIdleFace->Setup("./¿¤¸°", "¿¤¸°_¾ó±¼_´ë±â.X");

	m_pIdleHair.reset(new cHair);
	m_pIdleHair->SetHairTM(&m_pIdleFace->GetHairTM());
	m_pIdleHair->Setup("./¿¤¸°", "¿¤¸°_Çì¾î_´ë±â.X");

	//°ø°İ»óÅÂ
	m_pAttackBody.reset(new cBody);
	m_pAttackBody->Setup("./¿¤¸°", "¿¤¸°_¸ö_°ø°İ.X");

	m_pAttackFace.reset(new cFace);
	m_pAttackFace->SetNeckTM(&m_pAttackBody->GetNeckTM());
	m_pAttackFace->Setup("./¿¤¸°", "¿¤¸°_¾ó±¼_°ø°İ.X");

	m_pAttackHair.reset(new cHair);
	m_pAttackHair->SetHairTM(&m_pAttackBody->GetHairTM());
	m_pAttackHair->Setup("./¿¤¸°", "¿¤¸°_Çì¾î_°ø°İ.X");

	//´Ş¸®±â»óÅÂ
	m_pRunBody.reset(new cBody);
	m_pRunBody->Setup("./¿¤¸°", "¿¤¸°_¸ö_´Ş¸®±â.X");

	m_pRunFace.reset(new cFace);
	m_pRunFace->SetNeckTM(&m_pRunBody->GetNeckTM());
	m_pRunFace->Setup("./¿¤¸°", "¿¤¸°_¾ó±¼_´Ş¸®±â.X");

	m_pRunHair.reset(new cHair);
	m_pRunHair->SetHairTM(&m_pRunBody->GetHairTM());
	m_pRunHair->Setup("./¿¤¸°", "¿¤¸°_Çì¾î_´Ş¸®±â.X");
}

cPlayer::~cPlayer( )
{
}

void cPlayer::Update( )
{
	__super::Update( );

	StateUpdate();
}

void cPlayer::Render( )
{
	__super::Render( );

	if ( this->GetCollider( ) )
	{
		this->GetCollider( )->Render( );
	}

	StateRender();
}

void cPlayer::KeyControl()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{

	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{

	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{

	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{

	}
}

void cPlayer::StateUpdate()
{
	if (m_sState == player_IDLE)
	{
		if (m_pIdleBody && m_sState == player_IDLE)
		{
			m_pIdleBody->Update();
		}

		if (m_pIdleHair)
		{
			m_pIdleHair->SetHairTM(&m_pIdleBody->GetHairTM());
			m_pIdleHair->Update();
		}

		if (m_pIdleFace)
		{
			m_pIdleFace->SetNeckTM(&m_pIdleBody->GetNeckTM());
			m_pIdleFace->Update();
		}
	}

	if (m_sState == player_ATTACK)
	{
		if (m_pAttackBody && m_sState == player_IDLE)
		{
			m_pAttackBody->Update();
		}

		if (m_pAttackHair)
		{
			m_pAttackHair->SetHairTM(&m_pAttackBody->GetHairTM());
			m_pAttackHair->Update();
		}

		if (m_pAttackFace)
		{
			m_pAttackFace->SetNeckTM(&m_pAttackBody->GetNeckTM());
			m_pAttackFace->Update();
		}
	}

	if (m_sState == player_RUN)
	{
		if (m_pRunBody && m_sState == player_IDLE)
		{
			m_pRunBody->Update();
		}

		if (m_pRunHair)
		{
			m_pRunHair->SetHairTM(&m_pRunBody->GetHairTM());
			m_pRunHair->Update();
		}

		if (m_pRunFace)
		{
			m_pRunFace->SetNeckTM(&m_pRunBody->GetNeckTM());
			m_pRunFace->Update();
		}
	}
}

void cPlayer::StateRender()
{
	if (m_sState == player_IDLE)
	{
		if (m_pIdleBody && m_sState == player_IDLE)
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
	}

	if (m_sState == player_ATTACK)
	{
		if (m_pAttackBody && m_sState == player_IDLE)
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
	}

	if (m_sState == player_RUN)
	{
		if (m_pRunBody && m_sState == player_IDLE)
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
	}
}