#pragma once
#include "Singleton.h"

#define g_pDeviceManager cDeviceManager::Get()
#define g_pD3DDevice cDeviceManager::Get()->GetDevice()
#define g_pD3DSprite cDeviceManager::Get()->GetSprite()

class cDeviceManager : 
	public TSingleton<cDeviceManager>
{
public:
	LPD3DXSPRITE GetSprite( );
	LPDIRECT3DDEVICE9 GetDevice();

protected:
	cDeviceManager( );
	virtual ~cDeviceManager( );

private:
	void SetupLight( );

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	LPD3DXSPRITE		m_pD3DSprite;
};

inline LPD3DXSPRITE cDeviceManager::GetSprite( )
{
	return m_pD3DSprite;
}