#include "stdafx.h"
#include "GameObject.h"

#include "cObjectManager.h"
#include "IController.h"
#include "ICollider.h"

GameObject::GameObject( const std::string& objName ) :
	m_objName( objName ),
	m_isActive( true ),
	m_collider( nullptr ),
	m_controller( nullptr ),
	m_pos( 0.f, 0.f, 0.f ),
	m_angle( 0.f, 0.f, 0.f ),
	m_scale( 1.f, 1.f, 1.f )
{
	D3DXMatrixIdentity( &m_matWorld );
	//ObjectManager::Get()->AddObject( this );
}

GameObject::~GameObject( )
{
	//ObjectManager::Get()->DeleteObject( this->GetName());
}

void GameObject::Update( )
{
	for ( auto& actionElem : m_actionMap )
	{
		actionElem.second->Update( g_pTimeManager->GetDeltaTime( ));
	}

	if ( this->GetController())
	{
		this->GetController()->Update( g_pTimeManager->GetDeltaTime( ));
	}
}

void GameObject::Render( )
{
}

void GameObject::SetAction( IAction* action )
{
	m_actionMap[action->GetIdentifier()] = action;
	action->SetDelegate( this );
	action->SetOwner( this );
}

void GameObject::SetCollider( ICollider* collider )
{
	m_collider.reset( collider );
	collider->SetOwner( this );
}

const std::unique_ptr<ICollider>& GameObject::GetCollider( )
{
	return m_collider;
}

void GameObject::SetController( IController * controller )
{
	m_controller.reset( controller);
}
