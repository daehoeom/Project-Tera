#include "stdafx.h"
#include "PickingTile.h"

#include "Console.h"
#include "TilePicker.h"
#include "DirectInput.h"


PickingTile::PickingTile( ) :
	IPickable( L"PickingTile", new TilePicker( 10000 ))
{
}

PickingTile::~PickingTile( )
{
}

static bool isLButtonClicked = false;
static D3DXVECTOR3 prevPickPos{ 0, 0, 0 };

void PickingTile::Update( )
{
	__super::Update( );
}

void PickingTile::Render( )
{
	__super::Render( );
}

void PickingTile::OnPickDown( 
	const D3DXVECTOR3& pickPos ) const
{
	prevPickPos = pickPos;
}

void PickingTile::OnPickStay(
	const D3DXVECTOR3& pickPos ) const
{
	if ( g_hierarchyWnd->GetSelectedItemIndex( ) != -1 )
	{
		auto selectedObject = g_hierarchyWnd->GetSelectedItemAsObject( );
		selectedObject->Move( pickPos-prevPickPos );
	}

	prevPickPos = pickPos;
}

void PickingTile::OnPickUp( 
	const D3DXVECTOR3& pickPos ) const
{
	prevPickPos = pickPos;
	isLButtonClicked = false;
}
