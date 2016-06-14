#include "stdafx.h"
#include "cBuildingObject.h"

#include "cDeviceManager.h"
#include "cBoundingBox.h"
#include "cObjLoader.h"
#include "cGroup.h"


cBuildingObject::cBuildingObject( 
	const std::string& objFilePath )
{
	cObjLoader loader;
	loader.Load( objFilePath.c_str( ), m_groupRepo );
}

cBuildingObject::~cBuildingObject( )
{
	for ( auto elem : m_groupRepo )
	{
		SAFE_RELEASE( elem );
	}
}

void cBuildingObject::Render( )
{
	__super::Render( );

	g_pD3DDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_LIGHTING, TRUE );
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &this->GetWorld( ));
	for ( auto elem : m_groupRepo )
	{
		elem->Render( );
	}
}

void cBuildingObject::Update( )
{
	__super::Update( );
}

void cBuildingObject::OnCollisionStay( 
	int colliderIndex, 
	cCollisionObject* rhs )
{
}

void cBuildingObject::OnCollisionEnter( 
	int colliderIndex, 
	cCollisionObject* rhs )
{
}

void cBuildingObject::OnCollisionEnd( 
	int colliderIndex, 
	cCollisionObject * rhs )
{
}
