#include "stdafx.h"
#include "IPickable.h"

#include "cDeviceManager.h"

IPickable::IPickable( const std::wstring& objName ) :
	IRenderable( objName )
{
}

IPickable::~IPickable( )
{
}