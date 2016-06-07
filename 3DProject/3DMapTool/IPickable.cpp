#include "stdafx.h"
#include "IPickable.h"

#include "cDeviceManager.h"
#include "DirectInput.h"


IPickable::IPickable( 
	const std::wstring& objName,
	IPicker* picker ) :

	cGameObject( objName ),
	m_picker( picker ),
	m_isPicked( false )
{
}

IPickable::~IPickable( )
{
}

void IPickable::Update( )
{
	__super::Update( );

	if ( cDirectInput::Get( )->GetMouseState(
		KeyState::PRESS, MouseType::LEFT ) )
	{
		D3DXVECTOR3 pickPos;
		if ( m_picker->IsPicked( &pickPos ))
		{
			OnPickStay( pickPos );
		}
	}
	
	if ( cDirectInput::Get( )->GetMouseState(
		KeyState::DOWN, MouseType::LEFT ) )
	{
		D3DXVECTOR3 pickPos;
		if ( m_picker->IsPicked( &pickPos ))
		{
			OnPickDown( pickPos );
			m_isPicked = true;
		}
	}
	 
	if ( cDirectInput::Get( )->GetMouseState(
		KeyState::UP, MouseType::LEFT ) )
	{
		D3DXVECTOR3 pickPos;
		m_picker->IsPicked( &pickPos ); // It Used to calculate picked position

		if ( m_isPicked )
		{
			OnPickUp( pickPos );
			m_isPicked = true;
		}
	}
}