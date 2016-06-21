#pragma once
#include "cSkinnedMesh.h"
#include "cNpcSkinnedMesh.h"

#define g_pSkinnedMeshManager cSkinnedMeshManager::Get()

class cSkinnedMeshManager 
	:public TSingleton<cSkinnedMeshManager>
{

private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;
	std::map<std::string, cNpcSkinnedMesh*> m_mapNpcSkinnedMesh;

public:
	cSkinnedMeshManager();
	virtual ~cSkinnedMeshManager();
	cSkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFile);
	cNpcSkinnedMesh* GetNpcSkinnedMesh(char* szFolder, char* szFile);
	void Destroy();
};

