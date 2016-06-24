#pragma once
#include "Singleton.h"

#define g_pTextureManager cTextureManager::Get()

class cTextureManager :
	public TSingleton<cTextureManager>
{
public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath, D3DXIMAGE_INFO* pImageInfo = NULL);
	
protected:
	cTextureManager( );
	virtual ~cTextureManager( );

private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
	std::map<std::string, D3DXIMAGE_INFO>		m_mapImageInfo;

};

