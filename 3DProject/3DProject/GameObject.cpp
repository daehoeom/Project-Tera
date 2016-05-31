#include "stdafx.h"
#include "GameObject.h"

#include "cObjectManager.h"
#include "ICollider.h"

cGameObject::cGameObject( const std::string& objName ) :
	m_objName( objName ),
	m_isActive( true ),
	m_collider( nullptr ),
	m_pos( 0.f, 0.f, 0.f ),
	m_angle( 0.f, 0.f, 0.f ),
	m_scale( 1.f, 1.f, 1.f )
{
	D3DXMatrixIdentity( &m_matWorld );
	cObjectManager::Get()->AddObject( this );
}

cGameObject::~cGameObject( )
{
	cObjectManager::Get()->DeleteObject( this->GetName());
}

void cGameObject::Update( )
{
	cFSM::Update( );
}

void cGameObject::Render( )
{
}

void cGameObject::SetCollider( ICollider* collider )
{
	m_collider.reset( collider );
	collider->SetOwner( this );
}

const std::unique_ptr<ICollider>& cGameObject::GetCollider( )
{
	return m_collider;
}

