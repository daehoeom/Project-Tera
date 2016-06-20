#pragma once
#include <type_traits>
#include "Singleton.h"
#include "IScene.h"

class cSceneManager :
	public TSingleton<cSceneManager>
{
public:
	cSceneManager( );
	virtual ~cSceneManager( );

	template <typename _SceneTy>
	void LoadScene( )
	{
		// Compile time assertion
		static_assert( std::is_base_of<IScene, _SceneTy>::value,
			"cSceneManager::LoadScene only accept class which based on IScene." );

		if ( m_currScene )
		{
			delete m_currScene;
			m_currScene = nullptr;

			cGameObjectManager::Get( )->ResetAllObject( );
		}
		
		m_currScene = new _SceneTy;
	}

	void Render( );
	void Update( );
	
private:
	IScene* m_currScene;
};

