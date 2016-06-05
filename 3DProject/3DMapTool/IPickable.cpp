#include "stdafx.h"
#include "IPickable.h"

#include "cDeviceManager.h"


IPickable::IPickable( const std::wstring& objName ) :
	cGameObject( objName )
{
}

IPickable::~IPickable( )
{
}