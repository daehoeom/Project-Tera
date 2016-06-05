#pragma once
#include "IRenderable.h"


class IPickDelegate
{
public:
//	void OnPicked( ) = 0;
};

class IPickable : 
	public IRenderable//,
	//public IPickDelegate
{
public:
	IPickable( const std::wstring& objName );
	virtual ~IPickable( ) = 0;

public:
	virtual bool IsPicked( D3DXVECTOR3* pickedPos ) const = 0;
};

