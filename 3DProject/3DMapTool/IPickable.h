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
	
private:
	virtual void OnPickDown( const D3DXVECTOR3& pickPos ) const {};
	virtual void OnPickStay( const D3DXVECTOR3& pickPos ) const {};
	virtual void OnPickUp( const D3DXVECTOR3& pickPos ) const {};

private:
	bool m_isPicked;
	std::unique_ptr<IPicker> m_picker;
};

