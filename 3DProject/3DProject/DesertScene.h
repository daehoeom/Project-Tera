#pragma once
#include "IScene.h"

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
	DesertScenePlane* m_plane;
};

