#pragma once

class cGroup;
class cMtlTex;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;

public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN const char* szFullPath,
		OUT std::vector<cGroup*>& vecGroup,
		IN D3DXMATRIXA16* mat = NULL);

	LPD3DXMESH Load(IN const char* szFullPath,
		OUT std::vector<cMtlTex*>& vecMtlTex,
		IN D3DXMATRIXA16* mat = NULL);

	void LoadMtlLib(const char* szFullPath);
};

