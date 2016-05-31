#include "stdafx.h"
#include "cCollisionObject.h"
#include "cCollisionManager.h"

#include "ICollider.h"

cCollisionObject::cCollisionObject(
	const std::string& objName ) :

	cGameObject( objName )
{
	cCollisionManager::Get( )->AddObject( this );
}

cCollisionObject::~cCollisionObject( )
{
	cCollisionManager::Get( )->EraseObject( this );
}

void cCollisionObject::Update( )
{
	__super::Update( );

	if ( this->GetCollider( ) )
	{
		this->GetCollider( )->Update( );
	}
}

void cCollisionObject::Render( )
{
	__super::Render( );

	if ( this->GetCollider( ) )
	{
		this->GetCollider( )->Render( );
	}
}

void cCollisionObject::SetCollider( ICollider* collider )
{
	m_collider.reset( collider );
	collider->SetOwner( this );
}

const std::unique_ptr<ICollider>& cCollisionObject::GetCollider( )
{
	return m_collider;
}