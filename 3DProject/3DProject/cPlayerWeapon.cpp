#include "stdafx.h"
#include "cPlayerWeapon.h"

#include "cBoundingSphere.h"
#include "Console.h"
#include "cEnemy.h"


cPlayerWeapon::cPlayerWeapon( 
	const D3DXVECTOR3& vPos,
	const D3DXMATRIXA16& matLocal,
	cGameObject* owner ) :
		IWeapon( owner )
{
	// 무기 충돌체
	this->AddCollider( new cBoundingSphere(
		D3DXVECTOR3( 0, 0, 0 ), 10.f )
	);
	this->GetColliderRepo()[0]->SetPosition(
		D3DXVECTOR3( GetPosition( ).x+matLocal._41, 
			GetPosition( ).y+matLocal._42, 
			GetPosition( ).z+matLocal._43 ) 
	);
	
	this->SetObjectType(ObjectType::ePlayer);
}


cPlayerWeapon::~cPlayerWeapon( )
{
}

void cPlayerWeapon::OnCollisionEnter( 
	int colliderIndex, 
	cCollisionObject * rhs )
{
	assert( this->GetOwner( ));
	Log( "WeaponEnter\n" );


	if ( rhs->GetObjectType( ) == 
		ObjectType::eMonster )
	{
		switch ( static_cast<cPlayer*>( this->GetOwner( ))
			->GetPlayerState( ))
		{
		case ePlayerState::PLAYER_COMBO1:
		case ePlayerState::PLAYER_COMBO2:
		case ePlayerState::PLAYER_COMBO3:
		case ePlayerState::PLAYER_COMBO4:
			{
				cEnemy* monster = static_cast<cEnemy*>( rhs );
				if ( monster->IsAbleAttacked( ))
				{
					Log( "ATTACKED!" );
					monster->SetCurrHp( monster->GetCurrHp( )-100 );
					monster->ResetAttackDelay( );
				}
			}
			break;
		}
	}
	
}

void cPlayerWeapon::OnCollisionStay( 
	int colliderIndex, 
	cCollisionObject * rhs )
{
	Log( "WeaponStay\n" );
}

void cPlayerWeapon::OnCollisionEnd( 
	int colliderIndex, 
	cCollisionObject * rhs )
{
	Log( "WeaponEnd\n" );
}

