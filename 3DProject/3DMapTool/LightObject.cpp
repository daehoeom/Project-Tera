#include "stdafx.h"
#include "LightObject.h"

#include "cDeviceManager.h"

int32_t LightObject::m_lightCount = 0;

LightObject::LightObject( const std::wstring& objName ) :
	cGameObject( objName )
{
	D3DXVECTOR3 vDir( 1, -1, 1 );
	D3DXVec3Normalize( &vDir, &vDir );

	D3DLIGHT9 stLight;
	ZeroMemory( &stLight, sizeof( D3DLIGHT9 ) );
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	stLight.Diffuse = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	stLight.Specular = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	stLight.Direction = vDir;

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
