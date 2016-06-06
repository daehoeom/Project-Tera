#include "stdafx.h"
#include "PickingTile.h"

#include "Console.h"
#include "TilePicker.h"


PickingTile::PickingTile( ) :
	IPickable( L"PickingTile", new TilePicker( 10 ))
{
}

PickingTile::~PickingTile( )
{
}

void PickingTile::Update( )
{
	__super::Update( );
}

void PickingTile::Render( )
{
	__super::Render( );
}

void PickingTile::OnPicked( 
	const D3DXVECTOR3& pickPos ) const
{
}