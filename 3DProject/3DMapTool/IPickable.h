#pragma once
#include "cGameObject.h"


class IPickDelegate
{
public:
//	virtual void OnPicked( ) = 0;
};

class IPickable : 
	public cGameObject//,
	//public IPickDelegate
{
public:
	IPickable( const std::wstring& objName );
	virtual ~IPickable( ) = 0;

	virtual bool IsPicked( const D3DXVECTOR3& pickedPos ) const = 0;
};

