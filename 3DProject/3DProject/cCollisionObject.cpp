#include "stdafx.h"
#include "cCollisionObject.h"
#include "cCollisionManager.h"

#include "ICollider.h"


cCollisionObject::cCollisionObject( )
{
	cCollisionManager::Get( )->AddObject( this );
}

cCollisionObject::~cCollisionObject( )
{
	//cCollisionManager::Get( )->EraseObject( this );

	for ( auto& elem : m_colliderRepo )
	{
		SAFE_DELETE( elem );
	}
}

void cCollisionObject::Update( )
{
	__super::Update( );
	for ( auto& colliderElem : m_colliderRepo )
	{
		colliderElem->Update();
	}
}

void cCollisionObject::Render( )
{
	__super::Render( );
	for ( auto& colliderElem : m_colliderRepo )
	{
		colliderElem->Render();
	}
}

void cCollisionObject::OnCollisionStay( 
	int colliderIndex,
	cCollisionObject* rhs )
{
}

void cCollisionObject::OnCollisionEnter( 
	int colliderIndex,
	cCollisionObject* rhs )
{
}

void cCollisionObject::OnCollisionEnd( 
	int colliderIndex,
	cCollisionObject* rhs )
{
}

void cCollisionObject::AddCollider( ICollider* collider )
{
	m_colliderRepo.push_back( collider );
	m_collidedRepo.push_back( bool( false ));
}
