#include "stdafx.h"
#include "PickingTile.h"

#include "Console.h"
#include "TilePicker.h"
#include "DirectInput.h"


PickingTile::PickingTile( ) :
	IPickable( L"PickingTile", new TilePicker( 10000 )),
	m_isLButtonClicked( false ),
	m_prevPickPos( {0,0,0} )
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

void PickingTile::OnPickDown( 
	const D3DXVECTOR3& pickPos )
{
	m_prevPickPos = pickPos;
}

void PickingTile::OnPickStay(
	const D3DXVECTOR3& pickPos )
{
	if ( g_hierarchyWnd->GetSelectedItemIndex( ) != -1 )
	{
		g_wasSomethingChanged = true;
		auto selectedObject = g_hierarchyWnd->GetSelectedItemAsObject( );
		selectedObject->Move( pickPos-m_prevPickPos );
	}

	m_prevPickPos = pickPos;
}

void PickingTile::OnPickUp( 
	const D3DXVECTOR3& pickPos )
{
	m_prevPickPos = pickPos;
	m_isLButtonClicked = false;
}
