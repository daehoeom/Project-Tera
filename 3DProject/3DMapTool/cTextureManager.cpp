#include "StdAfx.h"
#include "cTextureManager.h"

#include "cDeviceManager.h"

cTextureManager::cTextureManager(void)
{
}


cTextureManager::~cTextureManager(void)
{
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
		HRESULT hr = D3DXCreateTextureFromFileA(g_pD3DDevice,
			sFullPath.c_str(),
			&pTexture);

		if(hr == D3D_OK)
		{
			m_mapTexture[sFullPath] = pTexture;
		}
		else 
		{
			return NULL;
		}
	}
	return m_mapTexture[sFullPath];
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
}
