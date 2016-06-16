#include "stdafx.h"
#include "ObjObject.h"

#include "PickUtil.h"
#include "cDeviceManager.h"
#include "BoundingBox.h"
#include "ObjRenderer.h"


cBuildingObject::cBuildingObject( const std::wstring& name ) :
	IColliseable( name )
{
}

cBuildingObject::~cBuildingObject( )
{
}

void cBuildingObject::Render( )
{
	__super::Render( );
}

void cBuildingObject::Update( )
{
	__super::Update( );
}
