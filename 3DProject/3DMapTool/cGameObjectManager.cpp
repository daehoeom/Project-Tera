#include "stdafx.h"
#include "cGameObjectManager.h"

#include "cDeviceManager.h"
//#include "cCollision.h"

cGameObjectManager::cGameObjectManager()
{
}

cGameObjectManager::~cGameObjectManager()
{
	for ( auto& elem : m_objMap )
	{
		SAFE_DELETE( elem.second );
	}
}

void cGameObjectManager::Update()
{
	for ( auto& object : m_objMap )
	{
		if ( object.second->IsActive( ))
		{
			object.second->Update( );
		}
	}
}

void cGameObjectManager::Render( )
{
	HRESULT hr = g_pD3DDevice->Clear( NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 47, 121, 112 ),
		1.0f, 0 );

	if ( SUCCEEDED( hr ))
	{
		g_pD3DDevice->BeginScene();

		for ( auto& object : m_objMap )
		{
			if ( object.second->IsActive())
			{
				object.second->Render();
			}
		}

		g_pD3DDevice->EndScene();
		g_pD3DDevice->Present( nullptr, nullptr, nullptr, nullptr );
	}
}
