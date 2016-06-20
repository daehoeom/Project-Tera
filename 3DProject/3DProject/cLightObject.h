#pragma once
#include "cGameObject.h"


class cLightObject :
	public cGameObject
{
public:
	cLightObject( );
	virtual ~cLightObject( );

	virtual void Update( ) override;

public:
	const D3DXVECTOR4& GetLightColor( ) const;

private:
	D3DXVECTOR4	m_lightColor;
};

inline const D3DXVECTOR4& cLightObject::GetLightColor( ) const
{
	return m_lightColor;
}