#include "stdafx.h"
#include "ObjObject.h"

#include "PickUtil.h"
#include "cDeviceManager.h"
#include "BoundingBox.h"
#include "cObjLoader.h"
#include "cGroup.h"

ObjObject::ObjObject( 
	const std::wstring& name,
	const std::string& filePath ) :
	IColliseable( name )
{
	cObjLoader objLoader;
	objLoader.Load( filePath.c_str(), m_vecGroup, nullptr );
	
	this->SetModelPath( filePath );
	this->SetCollider( new BoundingBox( 
		objLoader.GetMinVector( ),
		objLoader.GetMaxVector( ))
	);
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
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &this->GetWorld( ));

	for ( auto& p : m_vecGroup )
	{
		p->Render( );
	}
}

void ObjObject::Update( )
{
}
