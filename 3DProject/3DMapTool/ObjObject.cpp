#include "stdafx.h"
#include "ObjObject.h"

#include "PickUtil.h"
#include "cDeviceManager.h"
#include "BoundingBox.h"
#include "cObjLoader.h"
#include "cGroup.h"


cBuildingObject::cBuildingObject( 
	const std::wstring& name, 
	const std::string& filePath, 
	ICollider* collider ) :
	IColliseable( name )
{
	cObjLoader objLoader;
	objLoader.Load( filePath.c_str(), m_vecGroup );
	
	this->SetModelPath( filePath );

	// Using Custom collider
	if ( collider )
	{
		this->SetCollider( collider );
	}
	// Or ( automatically created collider )
	else
	{
		this->SetCollider( new BoundingBox( 
			objLoader.GetMinVector( ),
			objLoader.GetMaxVector( ))
		);
	}
}

cBuildingObject::~cBuildingObject( )
{
	for each( auto p in m_vecGroup )
	{
		SAFE_RELEASE( p );
	}
	m_vecGroup.clear( );
}

void cBuildingObject::Render( )
{
	__super::Render( );

	g_pD3DDevice->SetTransform( D3DTS_WORLD, &this->GetWorld( ));

	for ( auto& p : m_vecGroup )
	{
		p->Render( );
	}
}

void cBuildingObject::Update( )
{
	__super::Update( );
}
