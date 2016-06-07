#pragma once
#include "cGameObject.h"

class LightObject : 
	public cGameObject
{
public:
	LightObject( const std::wstring& objName );
	virtual ~LightObject( );

	virtual void SetActive( bool isActive );
	virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kLight; }

private:
	static int32_t m_lightCount;
	int32_t m_myLightIndex;
	D3DLIGHT9 m_light;
};

