#include "stdafx.h"
#include "GameObject.h"

#include "cObjectManager.h"
#include "ICollider.h"

GameObject::GameObject( const std::string& objName ) :
	m_objName( objName ),
	m_isActive( true ),
	m_collider( nullptr ),
	m_pos( 0.f, 0.f, 0.f ),
	m_angle( 0.f, 0.f, 0.f ),
	m_scale( 1.f, 1.f, 1.f )
{
	D3DXMatrixIdentity( &m_matWorld );
	//ObjectManager::Get()->AddObject( this );
}

GameObject::~GameObject( )
{
	delete m_collider;
	//ObjectManager::Get()->DeleteObject( this->GetName());
}

void GameObject::Update( )
{
	cFSM::Update( );
}

void GameObject::Render( )
{
}

void GameObject::SetCollider( ICollider* collider )
{
	m_collider = collider;
	collider->SetOwner( this );
}

ICollider* GameObject::GetCollider( )
{
	return m_collider;
}

