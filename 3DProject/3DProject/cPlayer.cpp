#include "stdafx.h"
#include "cPlayer.h"

#include "cPlayerController.h"
#include "cBoundingBox.h"


cPlayer::cPlayer( ) :
	GameObject( "Game" )
{
	this->SetController( new cPlayerController( this ));

	this->SetCollider( new cBoundingBox( this,
		D3DXVECTOR3( -1.f,-1.f,-1.f ), D3DXVECTOR3( 1.f, 1.f, 1.f )));
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

	this->GetCollider( )->Render( );
}