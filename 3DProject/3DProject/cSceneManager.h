#pragma once
#include "Singleton.h"
#include "IScene.h"

class SceneManager :
	public TSingleton<SceneManager>
{
public:
	SceneManager( );
	virtual ~SceneManager( );

	void LoadScene( IScene* newScene );
	void Render( );
	void Update( );
	
private:
	IScene* m_currScene;
};

