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
	virtual void OnPicked( const D3DXVECTOR3& pickPos ) const = 0;

private:
	std::unique_ptr<IPicker> m_picker;
};

