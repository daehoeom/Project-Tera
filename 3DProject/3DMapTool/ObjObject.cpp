#include "stdafx.h"
#include "ObjObject.h"

#include "cDeviceManager.h"

ObjObject::ObjObject( 
	const std::wstring& name,
	const std::string& filePath ) :
	
	cGameObject( name )
{
	cObjLoader objLoader;
	objLoader.Load( filePath.c_str(), m_vecGroup, nullptr );
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