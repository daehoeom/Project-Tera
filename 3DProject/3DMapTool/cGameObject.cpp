#include "stdafx.h"
#include "cGameObject.h"

#include "cGameObjectManager.h"

cGameObject::cGameObject( 
	const std::wstring& objName ) :
	
	m_objName( objName ),
	m_isActive( true ),
	m_pos( 0.f, 0.f, 0.f ),
	m_angle( 0.f, 0.f, 0.f ),
	m_scale( 1.f, 1.f, 1.f )
{
	D3DXMatrixIdentity( &m_matWorld );
	cGameObjectManager::Get()->AddObject(this);
}

cGameObject::~cGameObject( )
{
}

void cGameObject::Update( )
{
}

void cGameObject::Render( )
{
}