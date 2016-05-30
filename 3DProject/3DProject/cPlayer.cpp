#include "stdafx.h"
#include "cPlayer.h"

#include "cBoundingBox.h"

cPlayer::cPlayer( ) :
	GameObject( "Game" )
{
	this->SetCollider( new cBoundingBox( this,
		D3DXVECTOR3( -1.f,-1.f,-1.f ), D3DXVECTOR3( 1.f, 1.f, 1.f )));
}

cPlayer::~cPlayer( )
{
}

void cPlayer::Update( )
{
}

void cPlayer::Render( )
{
	this->GetCollider( )->Render( );
}
