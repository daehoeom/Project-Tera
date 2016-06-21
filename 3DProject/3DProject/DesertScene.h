#pragma once
#include <thread>
#include "cEnemy.h"
#include "IScene.h"

class cSprite;
class DesertScenePlane;
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
	DWORD m_loadSuccess;
	cSprite* m_loadingSprite;
	DesertScenePlane* m_plane;
	std::vector<cEnemy*> m_monsterRepo;
};

