#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
	for ( auto& elem : m_mapTexture )
	{
		SAFE_RELEASE( elem.second );
	}
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char* szFullPath)
{
	return GetTexture(std::string(szFullPath));
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string szFullPath, D3DXIMAGE_INFO* pImageInfo)
{
	if (pImageInfo)
	{
		if (m_mapTexture.find(szFullPath) == m_mapTexture.end() ||
			m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
		{
			SAFE_RELEASE(m_mapTexture[szFullPath]);
			D3DXCreateTextureFromFileEx(
				g_pD3DDevice,
				szFullPath.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				0,
				D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_DEFAULT,
				0,//D3DCOLOR_XRGB(255, 255, 255),
				&m_mapImageInfo[szFullPath],
				NULL,
				&m_mapTexture[szFullPath]);
		}

		*pImageInfo = m_mapImageInfo[szFullPath];
	}
	else
	{
		if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
		{
			LPDIRECT3DTEXTURE9 pTexture = NULL;
			HRESULT hr = D3DXCreateTextureFromFile(g_pD3DDevice,
				szFullPath.c_str(),
				&pTexture);

			if (hr == D3D_OK)
			{
				m_mapTexture[szFullPath] = pTexture;
			}
			else
			{
				return NULL;
			}
		}
	}

	return m_mapTexture[szFullPath];
}