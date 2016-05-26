#include "stdafx.h"
#include "GameObject.h"

#include "ObjectManager.h"
#include "IController.h"


GameObject::GameObject( const std::string& objName ) :
	m_objName( objName ),
	m_isActive( true ),
	m_controller( nullptr ),
	m_pos( 0.f, 0.f, 0.f ),
	m_angle( 0.f, 0.f, 0.f ),
	m_scale( 1.f, 1.f, 1.f )
{
	ObjectManager::Get( )->AddObject( this );
}

GameObject::~GameObject( )
{
	ObjectManager::Get( )->DeleteObject( this->GetName( ));
}

void GameObject::Update( float tickTime )
{
	for ( auto& actionElem : m_actionMap )
	{
		actionElem.second->Update( tickTime );
	}

	if ( this->GetController( ) )
		this->GetController( )->Update( tickTime );
}

void GameObject::SetAction( IAction* action )
{
	m_actionMap[action->GetIdentifier( )] = action;
	action->SetDelegate( this );
	action->SetOwner( this );
}

void GameObject::SetController( IController * controller )
{
	m_controller = controller;
}
