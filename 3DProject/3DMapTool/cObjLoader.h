#pragma once

class cGroup;
class cMtlTex;

class cObjLoader
{
public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN char* szFullPath, 
		OUT std::vector<cGroup*>& vecGroup,
		IN D3DXMATRIXA16* mat = NULL);
	void LoadMtlLib(char* szFullPath);

private:
	std::map<std::string, std::shared_ptr<cMtlTex*>> m_mapMtlTex;
};

