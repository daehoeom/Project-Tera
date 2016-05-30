#include "StdAfx.h"
#include "cSkinnedMeshManager.h"


cSkinnedMeshManager::cSkinnedMeshManager( )
{
}


cSkinnedMeshManager::~cSkinnedMeshManager( )
{
}

cSkinnedMesh* cSkinnedMeshManager::GetSkinnedMesh(char* szFolder, char* szFile)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string(szFile);

	if (m_mapSkinnedMesh.find(sFullPath) == m_mapSkinnedMesh.end())
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
		pSkinnedMesh->Load(szFolder, szFile);
		m_mapSkinnedMesh[sFullPath] = pSkinnedMesh;
	}

	return m_mapSkinnedMesh[sFullPath];
}

void cSkinnedMeshManager::Destroy()
{
	if ( m_mapSkinnedMesh.size( ) != 0 )
	{
		for (auto& elem : m_mapSkinnedMesh)
		{
			elem.second->Destroy();
		}
	}
}
