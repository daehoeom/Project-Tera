#pragma once
#include "cGameObject.h"
#include "IRenderer.h"

class IRenderable : 
	public cGameObject
{
public:
	IRenderable( const std::wstring& objName );
	virtual ~IRenderable( ) = 0;

	virtual void Render( );

public:
	// Sets
	void SetModelPath( const std::string & modelPath );
	void SetRenderer( IRenderer* );

	// Gets
	const std::string& GetModelPath( ) const;
	IRenderer* GetRenderer( );

private:
	IRenderer* m_renderer;
	std::string m_modelPath;
};


inline void IRenderable::SetModelPath(
	const std::string & modelPath )
{
	m_modelPath = modelPath;
}

inline void IRenderable::SetRenderer( 
	IRenderer * renderer )
{
	SAFE_DELETE( m_renderer );

	m_renderer = renderer;
	renderer->SetOwner( this );
}

inline const std::string& IRenderable::GetModelPath( ) const
{
	return m_modelPath;
}

inline IRenderer * IRenderable::GetRenderer( )
{
	return m_renderer;
}
