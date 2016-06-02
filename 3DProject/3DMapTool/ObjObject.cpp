#include "stdafx.h"
#include "ObjObject.h"

#include "cDeviceManager.h"

ObjObject::ObjObject( 
	const std::string& name,
	const std::string& filePath ) :
	
	cGameObject( name )
{
	m_objLoader.Load( filePath.c_str(), m_vecGroup, nullptr );
}

ObjObject::~ObjObject( )
{

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