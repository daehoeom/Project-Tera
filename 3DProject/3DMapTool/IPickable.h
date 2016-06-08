#pragma once
#include "cGameObject.h"
#include "IPicker.h"


class IPickable : 
	public cGameObject
{
public:
	IPickable( const std::wstring& objName, IPicker* picker );
	virtual ~IPickable( ) = 0;

	virtual void Update( ) override;
	
public:
	const std::unique_ptr<IPicker>& GetPicker( ) const { return m_picker; }

private:
	virtual void OnPickDown( const D3DXVECTOR3& pickPos ) {};
	virtual void OnPickStay( const D3DXVECTOR3& pickPos ) {};
	virtual void OnPickUp( const D3DXVECTOR3& pickPos ) {};

private:
	bool m_isPicked;
	std::unique_ptr<IPicker> m_picker;
};

inline D3DXVECTOR3 CalculatePickPos( 
	IPickable* pickObj )
{
	D3DXVECTOR3 pickPos;
	pickObj->GetPicker( )->IsPicked( &pickPos );

	return pickPos;
}