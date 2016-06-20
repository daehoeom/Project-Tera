#pragma once
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

class TestScene :
	public IScene
{
public:
	TestScene( );
	virtual ~TestScene( );

	virtual void Render( ) override;
	virtual void Update( ) override;

private:
	TestScenePlane* m_plane;
};