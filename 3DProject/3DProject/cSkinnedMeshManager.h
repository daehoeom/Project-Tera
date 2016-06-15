#pragma once
#include "cSkinnedMesh.h"

#define g_pSkinnedMeshManager cSkinnedMeshManager::Get()

class cSkinnedMeshManager 
	:public TSingleton<cSkinnedMeshManager>
{

private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;

public:
	cSkinnedMeshManager();
	virtual ~cSkinnedMeshManager();
	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFile);
	void Destroy();
};

