#pragma once
#include "IPickable.h"

class PickingTile : 
	public IPickable
{
public:
	PickingTile( );
	virtual ~PickingTile( );

	virtual void Update( ) override;
	virtual void Render( ) override;

	virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kUnknown; }

private:
	virtual void OnPicked( const D3DXVECTOR3& pickPos ) const;
};

