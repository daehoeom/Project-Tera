#pragma once
#include "Singleton.h"

#define g_pTextureManager cTextureManager::Get()

class cTextureManager :
	public TSingleton<cTextureManager>
{
public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath);

protected:
	cTextureManager( ) {};
	virtual ~cTextureManager( );

private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
};

