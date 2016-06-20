#pragma once
#include <thread>
#include "IScene.h"

class cBuildingObject;
class cPlayer;
class cGrid;
class cSkyBox;
class cObjLoader;
class cGroup;
class cNpcManager;
class cArgoniteKallashGuardLeader;
class TestScenePlane;
class cSprite;

class TestScene :
	public IScene
{
public:
	TestScene( );
	virtual ~TestScene( );

	virtual void Render( ) override;
	virtual void Update( ) override;

private:
	std::thread m_loadThread;
	DWORD m_loadSuccess;
	cSprite* m_loadingSprite;
	TestScenePlane* m_plane;
};