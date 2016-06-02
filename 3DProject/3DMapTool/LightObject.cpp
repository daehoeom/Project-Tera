#include "stdafx.h"
#include "LightObject.h"

#include "cDeviceManager.h"

int32_t LightObject::m_lightCount = 0;

LightObject::LightObject( const std::wstring& objName ) :
	cGameObject( objName )
{
	D3DLIGHT9 stLight;
	ZeroMemory( &stLight, sizeof( D3DLIGHT9 ));
	stLight.Type = D3DLIGHT_POINT;
	stLight.Ambient = D3DXCOLOR( 0.f, 0.7f, 0.f, 1.0f );
	stLight.Diffuse = D3DXCOLOR( 0.f, 0.7f, 0.f, 1.0f );
	stLight.Specular = D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );
	stLight.Position = D3DXVECTOR3( 0, 0, 0 );
	stLight.Range = 2.0f;

	g_pD3DDevice->SetLight( m_lightCount, &stLight );
	g_pD3DDevice->LightEnable( m_lightCount, true );
	
	m_myLightIndex = m_lightCount++;
}

LightObject::~LightObject( )
{
}

void LightObject::SetActive( bool isActive )
{
	__super::SetActive( isActive );

	g_pD3DDevice->LightEnable( 
		m_myLightIndex, isActive );
}
