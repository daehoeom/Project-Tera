#pragma once
#include "cBuildingObject.h"
#include "IScene.h"

class cPlayer;
class cGrid;
class cSkyBox;
class cObjLoader;
class cGroup;
class cNpcManager;
class cArgoniteKallashGuardLeader;

class TestScene :
	public IScene
{
public:
	explicit TestScene( const std::string& xmlPath );
	virtual ~TestScene( );

	virtual void Render( ) override;
	virtual void Update( ) override;

private:
	void ReadXML( const std::string& xmlPath );

private:
	cGrid* m_pGrid;
	cSkyBox* m_pSkyBox;
	cObjLoader* m_pLoader;
	cNpcManager* m_pNpc;
	cArgoniteKallashGuardLeader* m_pMonster;
	cArgoniteKallashGuardLeader* m_pMonster2;
	std::vector<cBuildingObject*> m_buildingObjectRepo;
};