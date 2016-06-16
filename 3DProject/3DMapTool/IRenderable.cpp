#include "stdafx.h"
#include "IRenderable.h"


#include "IRenderer.h"

IRenderable::IRenderable( 
	const std::wstring& objName ) :
		m_renderer( nullptr ),
		cGameObject( objName )
{
}

IRenderable::~IRenderable( )
{
	SAFE_DELETE( m_renderer )
}

void IRenderable::Render( )
{
	if ( m_renderer )
	{
		m_renderer->Render( );
	}
}
