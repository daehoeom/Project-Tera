#include "stdafx.h"
#include "IPickable.h"

#include "cDeviceManager.h"
#include "DirectInput.h"


IPickable::IPickable( 
	const std::wstring& objName,
	IPicker* picker ) :

	cGameObject( objName ),
	m_picker( picker )
{
}

IPickable::~IPickable( )
{
}

void IPickable::Update( )
{
	__super::Update( );

	if ( cDirectInput::Get( )->GetMouseState(
		KeyState::DOWN, MouseType::LEFT ) )
	{
		D3DXVECTOR3 pickPos;
		if ( m_picker->IsPicked( &pickPos ))
		{
			OnPicked( pickPos );
		}
	}
}