#include "stdafx.h"
#include "cPlayer.h"

#include "cBoundingBox.h"
#include "cPlayerState.h"

cPlayer::cPlayer( ) :
	GameObject( "Player" )
{
	this->AddState( eFSMState::kIdle, new cPlayerIdleState( this ));
	this->SetCollider( new cBoundingBox( this, D3DXVECTOR3( -1.f,-1.f,-1.f ), D3DXVECTOR3( 1.f, 1.f, 1.f )));

	this->TranslateState( eFSMState::kIdle );
}

cPlayer::~cPlayer( )
{
}

void cPlayer::Update( )
{
	__super::Update( );
}

void cPlayer::Render( )
{
	__super::Render( );

	if ( this->GetCollider( ) )
	{
		this->GetCollider( )->Render( );
	}
}