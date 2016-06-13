#pragma once
#include "Singleton.h"
#include "IScene.h"

class cSceneManager :
	public TSingleton<cSceneManager>
{
public:
	cSceneManager( );
	virtual ~cSceneManager( );

	void LoadScene( IScene* newScene );
	void Render( );
	void Update( );
	
private:
	IScene* m_currScene;
};

