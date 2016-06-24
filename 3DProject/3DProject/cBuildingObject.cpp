#include "stdafx.h"
#include "cBuildingObject.h"
#include "cDeviceManager.h"
#include "cBoundingBox.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cShaderManager.h"
#include "cLightObject.h"
#include "cGameObjectManager.h"

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


cObjRenderer::cObjRenderer( 
	const char* objFilePath ):
	m_effect( cShaderManager::Get( )->GetShader( 
		"Shader/DiffuseSpecularLightinh.fx" ))
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
		SAFE_DELETE( groupElem )
	}
}

void cObjRenderer::Render( )
{
	assert( this->GetOwner( ));
	
	m_effect->SetTechnique( "Lighting" );

	m_effect->SetMatrix( "gWorldMatrix", &this->GetOwner( )->GetWorld( ));
	m_effect->SetMatrix( "gViewMatrix", &cCamera::Get( )->GetView( ));
	m_effect->SetMatrix( "gProjectionMatrix", &cCamera::Get( )->GetProjection( ) );

	m_effect->SetVector( "gWorldLightPosition", 
		&D3DXVECTOR4( g_lightObject->GetPosition( ), 1.f ));
	m_effect->SetVector( "gWorldCameraPosition", 
		&D3DXVECTOR4( cCamera::Get( )->GetEye( ), 1.f ));

	UINT numPasses = 0;
	m_effect->Begin( &numPasses, NULL );
	{
		for ( UINT i = 0; i < numPasses; ++i )
		{
			m_effect->BeginPass( i );
			{
				for ( auto& groupElem : m_groupRepo )
				{
					groupElem->Render( );
				}
			}
			m_effect->EndPass( );
		}
	}
	m_effect->End( );
}


cXRenderer::cXRenderer( 
	const char* xFilePath )
{
	if ( FAILED( D3DXLoadMeshFromXA( xFilePath, D3DXMESH_SYSTEMMEM, 
			g_pD3DDevice, NULL, NULL, NULL, &m_mtrlCount, &m_mesh )))
	{
		MessageBoxA( GetFocus( ),
			( std::string( "Failed to load x file. ( " ) + xFilePath + std::string( " )" )).c_str( ),
			"WARNING!",
			MB_OK | MB_ICONEXCLAMATION 
		);
	};

	this->SetupMinAndMax( );
}

cXRenderer::~cXRenderer( )
{
	SAFE_RELEASE( m_mesh );
}

void cXRenderer::Render( )
{
	assert( this->GetOwner( ) );

	if ( m_mesh )
	{
		for ( int i = 0; i < m_mtrlCount; ++i )
		{
			m_mesh->DrawSubset( i );
		}
	}
}

void cXRenderer::SetupMinAndMax( )
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
		m_renderer = new cObjRenderer( objFilePath.c_str( ));
		break;

	case ExtensionTable::kX:
		m_renderer = new cXRenderer( objFilePath.c_str( ));
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
		m_renderer->Render();
	}
}

void cBuildingObject::Update( )
{
	__super::Update( );

	D3DXMATRIX matProj, matView;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

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

cPlaneObject::cPlaneObject( const std::string & modelFilePath ) :
	m_renderer( nullptr )
{
	switch ( AnalyzeExtension( modelFilePath ))
	{
	case ExtensionTable::kObj:
		m_renderer = new cObjRenderer( modelFilePath.c_str( ));
		break;

	case ExtensionTable::kX:
		m_renderer = new cXRenderer( modelFilePath.c_str( ));
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

cPlaneObject::~cPlaneObject( )
{
	SAFE_DELETE( m_renderer );
}

IRenderer* cPlaneObject::GetRenderer( )
{
	return m_renderer;
}

void cPlaneObject::Render( )
{
	__super::Render( );
	
	if ( m_renderer )
	{
		m_renderer->Render( );
	}
}

void cPlaneObject::Update( )
{
	__super::Update( );
}
