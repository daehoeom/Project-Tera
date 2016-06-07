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

	for (ICollider* elem : m_collider)
	{
		SAFE_DELETE(elem);
	}
}

void cCollisionObject::Update( )
{
	__super::Update( );


	for (auto colliderElem : m_collider)
	{
		colliderElem->Update();
	}
}

void cCollisionObject::Render( )
{
	__super::Render( );

	for (auto colliderElem : m_collider)
	{
		colliderElem->Render();
	}
}

void cCollisionObject::OnCollisionStay( 
	cCollisionObject* rhs )
{
	this->SetCollision(true);
}

void cCollisionObject::OnNotCollision(cCollisionObject* rhs)
{
	if (this->GetCollision())
		this->SetCollision(false);
}

void cCollisionObject::SetCollider( ICollider* collider )
{
	m_collider.push_back( collider );
}

std::vector<ICollider*>& cCollisionObject::GetColliderRepo()
{
	return m_collider;
}