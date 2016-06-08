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

	virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kPickTile; }

private:
	virtual void OnPickDown( const D3DXVECTOR3& pickPos ) override;
	virtual void OnPickStay( const D3DXVECTOR3& pickPos ) override;
	virtual void OnPickUp( const D3DXVECTOR3& pickPos ) override;

private:
	bool m_isLButtonClicked;
	D3DXVECTOR3 m_prevPickPos;
};

