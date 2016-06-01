#pragma once



class cObjLoader
{
private:
	std::map<std::string, SpMtlTex> m_mapMtlTex;

public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN char* szFullPath,
		OUT std::vector<SpGroup>& vecGroup,
		IN D3DXMATRIXA16* mat = NULL);
	void LoadMtlLib(char* szFullPath);
};

