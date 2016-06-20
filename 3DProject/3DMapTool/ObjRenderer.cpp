#include "stdafx.h"
#include "ObjRenderer.h"

#include "cObjLoader.h"
#include "cGroup.h"
#include "cDeviceManager.h"
#include "IRenderable.h"


cObjRenderer::cObjRenderer( 
	const char* objFilePath )
{
	cObjLoader loader;
	loader.Load( objFilePath, m_groupRepo );

	m_min = loader.GetMinVector( );
	m_max = loader.GetMaxVector( );
}

cObjRenderer::~cObjRenderer( )
{
	for ( auto& groupElem : m_groupRepo )
	{
		SAFE_RELEASE( groupElem )
	}
}

void cObjRenderer::Render( )
{
	assert( this->GetOwner( ));
	
	g_pD3DDevice->SetTransform( D3DTS_WORLD, 
		&this->GetOwner( )->GetWorld( ) );

	for ( auto& groupElem : m_groupRepo )
	{
		groupElem->Render( );
	}
}
