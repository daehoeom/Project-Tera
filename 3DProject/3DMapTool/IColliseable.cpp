#include "stdafx.h"
#include "IColliseable.h"


IColliseable::IColliseable( 
	const std::wstring& objName,
	ICollider* collider ) :
	IRenderable( objName ),

	m_collider( collider ),
	m_isDebugRender( true )
{
}

IColliseable::~IColliseable( )
{
	SAFE_DELETE( m_collider );
}

void IColliseable::Update( )
{
	__super::Update( );

	if ( m_collider )
	{
		m_collider->Update( this->GetWorld( ));
	}
}

void IColliseable::Render( )
{
	__super::Render( );

	if ( m_isDebugRender && 
		m_collider )
	{
		m_collider->Render( );
	}
}

void IColliseable::SetCollider(
	ICollider* collider )
{
	SAFE_DELETE( m_collider );
	m_collider = collider;
}

ICollider* IColliseable::GetCollider( )
{
	return m_collider;
}

const ICollider* IColliseable::GetCollider( ) const
{
	return m_collider;
}

void IColliseable::SetDebugRender(
	bool isDebugRender )
{
	m_isDebugRender = isDebugRender;
}

