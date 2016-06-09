#include "stdafx.h"
#include "ObjObject.h"

#include "cDeviceManager.h"
#include "cBoundingBox.h"
#include "cObjLoader.h"
#include "cGroup.h"


ObjObject::ObjObject( 
	const std::string& name, 
	const std::string& filePath, 
	ICollider* collider ) :
	cCollisionObject( name )
{
	cObjLoader objLoader;
	objLoader.Load( filePath.c_str(), m_vecGroup );
	
	// Collider passed : Parsed or custom 
	if ( collider )
	{
		this->SetCollider( collider );
	}
	// Create collider automatically
	else
	{
		this->SetCollider( new cBoundingBox(
			objLoader.GetMinVector( ),
			objLoader.GetMaxVector( ))
		);
	}
}

ObjObject::~ObjObject( )
{
	for each( auto p in m_vecGroup )
	{
		SAFE_RELEASE( p );
	}
	m_vecGroup.clear( );
}

void ObjObject::Render( )
{
	__super::Render( );

	g_pD3DDevice->SetTransform( D3DTS_WORLD, &this->GetWorld( ));

	for ( auto& p : m_vecGroup )
	{
		p->Render( );
	}
}

void ObjObject::Update( )
{
	__super::Update( );
}
