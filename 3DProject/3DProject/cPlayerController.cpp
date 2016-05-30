#include "stdafx.h"
#include "cPlayerController.h"

cPlayerController::cPlayerController( class GameObject* owner ) :
	IController( owner ),
	m_dirVec( 0,0,1 )
{
}

cPlayerController::~cPlayerController( )
{
}

void cPlayerController::Update( )
{
	const float rotSpeed = 0.01f;
	const float moveSpeed = 0.1f;

	if ( cKeyManager::Get( )->isStayKeyDown( VK_SPACE ))
	{
		this->GetOwner( )->Move( m_dirVec * moveSpeed );
	}

	if ( cKeyManager::Get( )->isStayKeyDown( VIRTUAL::VK_A ) )
	{
		this->GetOwner( )->Rotate({ 0.f, 0.01f, 0.f });

		D3DXMATRIXA16 matRotY;
		D3DXMatrixRotationY( &matRotY, this->GetOwner( )->GetAngle( ).y );

		D3DXVECTOR3 dirVec( 0, 0, 1 );
		D3DXVec3TransformCoord( &m_dirVec, &dirVec, &matRotY );
	}
}
