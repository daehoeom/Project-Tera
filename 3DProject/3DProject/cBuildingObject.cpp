#include "stdafx.h"
#include "cBuildingObject.h"

#include "cDeviceManager.h"
#include "cBoundingBox.h"
#include "cObjLoader.h"
#include "cGroup.h"

namespace
{

enum ExtensionTable
{
	kUnknown,
	kX,
	kXML,
	kRaw8,
	kRaw16,
	kObj,
};

ExtensionTable AnalyzeExtension( 
	const std::string& filePath )
{
	int i = filePath.size( )-1; 
	while ( i >= 0 &&
		filePath[i] != '.' )
	{
		--i;
	}

	std::string extension = filePath.substr( i+1, filePath.size( ));
	for ( auto& charElem : extension )
	{
		charElem = tolower( charElem );
	}

	if ( extension == "x" )
	{
		return ExtensionTable::kX;
	}
	else if ( extension == "obj" )
	{
		return ExtensionTable::kObj;
	}
	else if ( extension == "raw" )
	{
		return ExtensionTable::kObj;
	}
	else if ( extension == "xml" )
	{
		return ExtensionTable::kXML;
	}
	else
	{
		return ExtensionTable::kUnknown;
	}
}

}


ObjRenderer::ObjRenderer( 
	const char* objFilePath )
{
	cObjLoader loader;
	loader.Load( objFilePath, m_groupRepo );

	m_min = loader.GetMinVector( );
	m_max = loader.GetMaxVector( );
}

ObjRenderer::~ObjRenderer( )
{
	for ( auto& groupElem : m_groupRepo )
	{
		SAFE_DELETE( groupElem )
	}
}

void ObjRenderer::Render( )
{
	assert( this->GetOwner( ));
	
	g_pD3DDevice->SetTransform( D3DTS_WORLD, 
		&this->GetOwner( )->GetWorld( ) );
	g_pD3DDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_LIGHTING, TRUE );

	for ( auto& groupElem : m_groupRepo )
	{
		groupElem->Render( );
	}
}

XRenderer::XRenderer( 
	const char* xFilePath )
{
	if ( FAILED( D3DXLoadMeshFromXA( xFilePath, D3DXMESH_SYSTEMMEM, 
			g_pD3DDevice, NULL, NULL, NULL, &m_mtrlCount, &m_mesh )))
	{
		MessageBox( GetFocus( ),
			"Failed to invoke D3DXLoadMeshFromXA.",
			"WARNING!",
			MB_OK | MB_ICONEXCLAMATION 
		);
	};

	this->SetupMinAndMax( );
}

XRenderer::~XRenderer( )
{
	SAFE_RELEASE( m_mesh );
}

void XRenderer::Render( )
{
	assert( this->GetOwner( ) );

	g_pD3DDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_LIGHTING, TRUE );
	g_pD3DDevice->SetTransform( D3DTS_WORLD,
		&this->GetOwner( )->GetWorld( ) );

	if ( m_mesh )
	{
		for ( int i = 0; i < m_mtrlCount; ++i )
		{
			m_mesh->DrawSubset( i );
		}
	}
}

void XRenderer::SetupMinAndMax( )
{
	assert( m_mesh );

	BYTE* pVertices = nullptr;
	m_mesh->LockVertexBuffer( D3DLOCK_READONLY, ( LPVOID* )&pVertices );

	D3DXComputeBoundingBox( ( D3DXVECTOR3* )pVertices,
		m_mesh->GetNumVertices( ), D3DXGetFVFVertexSize( m_mesh->GetFVF( ) ),
		&m_min, &m_max );

	m_mesh->UnlockVertexBuffer( );
}



cBuildingObject::cBuildingObject( 
	const std::string& objFilePath ) :
	m_renderer( nullptr )
{
	switch ( AnalyzeExtension( objFilePath ))
	{
	case ExtensionTable::kObj:
		m_renderer = new ObjRenderer( objFilePath.c_str( ));
		break;

	case ExtensionTable::kX:
		m_renderer = new XRenderer( objFilePath.c_str( ));
		break;

	default:
		MessageBox(
			GetFocus( ),
			"Failed to analyze extension.",
			"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
		break;
	}

	m_renderer->SetOwner( this );
}

cBuildingObject::~cBuildingObject( )
{
	SAFE_DELETE( m_renderer );
}

void cBuildingObject::Render( )
{
	__super::Render( );

	if ( m_renderer )
	{
		m_renderer->Render( );
	}
}

void cBuildingObject::Update( )
{
	__super::Update( );
}

void cBuildingObject::OnCollisionStay( 
	int colliderIndex, 
	cCollisionObject* rhs )
{
}

void cBuildingObject::OnCollisionEnter( 
	int colliderIndex, 
	cCollisionObject* rhs )
{
}

void cBuildingObject::OnCollisionEnd( 
	int colliderIndex, 
	cCollisionObject * rhs )
{
}
