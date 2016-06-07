#include "StdAfx.h"
#include "cTextureManager.h"

#include "cDeviceManager.h"


cTextureManager::~cTextureManager( )
{
	for ( auto& iter : m_mapTexture )
	{
		SAFE_RELEASE( iter.second );
	}
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( char* szFullPath )
{
	return GetTexture(std::string(szFullPath));
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( std::string sFullPath )
{
	if (m_mapTexture.find(sFullPath) == m_mapTexture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = NULL;
		HRESULT hr = D3DXCreateTextureFromFileA(
			g_pD3DDevice,
			sFullPath.c_str(),
			&pTexture);

		if(hr == D3D_OK)
		{
			m_mapTexture[sFullPath] = pTexture;
		}
		else 
		{
			std::string str = "텍스처 로딩에 실패했습니다. (";
			str += sFullPath;
			str += ')';

			MessageBoxA( GetFocus( ), str.c_str( ),
				"WARNING!", MB_OK | MB_ICONEXCLAMATION );
			
			return NULL;
		}
	}

	return m_mapTexture[sFullPath];
}

