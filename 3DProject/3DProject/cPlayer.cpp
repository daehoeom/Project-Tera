#include "stdafx.h"
#include "cPlayer.h"
#include "cBoundingBox.h"
#include "cPlayerState.h"

#include "cBody.h"
#include "cHair.h"
#include "cFace.h"

cPlayer::cPlayer( ) :
	cCollisionObject( "Player" )
{
	this->SetCollider( new cBoundingBox( this, D3DXVECTOR3( -1.f,-1.f,-1.f ), D3DXVECTOR3( 1.f, 1.f, 1.f )));
	this->TranslateState( eFSMState::kAttack );

	//´ë±â»óÅÂ
	m_pIdleBody.reset(new cBody);
	m_pIdleBody->Setup("./CH/¿¤¸°", "¿¤¸°_¸ö_´ë±â.X");

	m_pIdleFace.reset(new cFace);
	m_pIdleFace->SetNeckTM(&m_pIdleBody->GetNeckTM());
	m_pIdleFace->Setup("./CH/¿¤¸°", "¿¤¸°_¾ó±¼_´ë±â.X");

	m_pIdleHair.reset(new cHair);
	m_pIdleHair->SetHairTM(&m_pIdleFace->GetHairTM());
	m_pIdleHair->Setup("./CH/¿¤¸°", "¿¤¸°_Çì¾î_´ë±â.X");

	//°ø°İ»óÅÂ
	m_pAttackBody.reset(new cBody);
	m_pAttackBody->Setup("./CH/¿¤¸°", "¿¤¸°_¸ö_°ø°İ.X");

	m_pAttackFace.reset(new cFace);
	m_pAttackFace->SetNeckTM(&m_pAttackBody->GetNeckTM());
	m_pAttackFace->Setup("./CH/¿¤¸°", "¿¤¸°_¾ó±¼_°ø°İ.X");

	m_pAttackHair.reset(new cHair);
	m_pAttackHair->SetHairTM(&m_pAttackBody->GetHairTM());
	m_pAttackHair->Setup("./CH/¿¤¸°", "¿¤¸°_Çì¾î_°ø°İ.X");

	//´Ş¸®±â»óÅÂ
	m_pRunBody.reset(new cBody);
	m_pRunBody->Setup("./CH/¿¤¸°", "¿¤¸°_¸ö_´Ş¸®±â.X");

	m_pRunFace.reset(new cFace);
	m_pRunFace->SetNeckTM(&m_pRunBody->GetNeckTM());
	m_pRunFace->Setup("./CH/¿¤¸°", "¿¤¸°_¾ó±¼_´Ş¸®±â.X");

	m_pRunHair.reset(new cHair);
	m_pRunHair->SetHairTM(&m_pRunBody->GetHairTM());
	m_pRunHair->Setup("./CH/¿¤¸°", "¿¤¸°_Çì¾î_´Ş¸®±â.X");
}

cPlayer::~cPlayer( )
{
}

void cPlayer::Update( )
{
	__super::Update( );

	SetUpdateState();
}

void cPlayer::Render( )
{
	__super::Render( );

	SetRenderState();
}
//
//void cPlayer::KeyControl()
//{
//	if (KEYMANAGER->isStayKeyDown('W'))
//	{
//
//	}
//
//	if (KEYMANAGER->isStayKeyDown('S'))
//	{
//
//	}
//
//	if (KEYMANAGER->isStayKeyDown('A'))
//	{
//
//	}
//
//	if (KEYMANAGER->isStayKeyDown('D'))
//	{
//
//	}
//}

void cPlayer::SetUpdateState()
{
	switch (this->GetCurrStateType())
	{
	case eFSMState::kIdle:
		if (m_pIdleBody)
		{
			m_pIdleBody->Update();
		}
		if (m_pIdleHair)
		{
			m_pIdleHair->SetHairTM(
				&m_pIdleBody->GetHairTM());
			m_pIdleHair->Update();
		}
		if (m_pIdleFace)
		{
			m_pIdleFace->SetNeckTM(
				&m_pIdleBody->GetNeckTM());
			m_pIdleFace->Update();
		}
		break;

	case eFSMState::kAttack:
		if (m_pAttackBody)
		{
			m_pAttackBody->Update();
		}
		if (m_pAttackHair)
		{
			m_pAttackHair->SetHairTM(
				&m_pAttackBody->GetHairTM());
			m_pAttackHair->Update();
		}
		if (m_pAttackFace)
		{
			m_pAttackFace->SetNeckTM(&m_pAttackBody->GetNeckTM());
			m_pAttackFace->Update();
		}
		break;

	case eFSMState::kMove:
		if (m_pRunBody)
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
		break;
	}
}

void cPlayer::SetRenderState()
{
	switch (this->GetCurrStateType())
	{
	case eFSMState::kIdle:
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

	case eFSMState::kAttack:
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

	case eFSMState::kMove:
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
