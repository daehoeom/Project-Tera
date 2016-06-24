#pragma once
#include <thread>
#include "cEnemy.h"
#include "IScene.h"

class cSprite;
class DesertScenePlane;
class DesertSceneOasis;
class DesertScene :
	public IScene
{
public:
	DesertScene( );
	virtual ~DesertScene( );

	virtual void Update( ) override;
	virtual void Render( ) override;

private:
	std::thread m_loadThread;
	DesertScenePlane* m_plane;
	DesertSceneOasis* m_oasis;
	DWORD m_loadSuccess;
	cSprite* m_loadingSprite;
	std::vector<cEnemy*> m_monsterRepo;
};

