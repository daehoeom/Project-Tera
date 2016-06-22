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
		if (CheckSphere(this->GetPosition().x, this->GetPosition().y, this->GetPosition().z, 30.f))
		{
			m_renderer->Render();
		}
	}
}

void cBuildingObject::Update( )
{
	__super::Update( );

	D3DXMATRIX matProj, matView;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	ConstructFrustum(1000.f, matProj, matView);
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

void cBuildingObject::ConstructFrustum(float screenDepth, D3DXMATRIX proj, D3DXMATRIX view)
{
	D3DXVECTOR3 v[8];

	v[0] = D3DXVECTOR3(-1, -1, 0);
	v[1] = D3DXVECTOR3(1, -1, 0);
	v[2] = D3DXVECTOR3(-1, 1, 0);
	v[3] = D3DXVECTOR3(1, 1, 0);
	v[4] = D3DXVECTOR3(-1, -1, 1);
	v[5] = D3DXVECTOR3(1, -1, 1);
	v[6] = D3DXVECTOR3(-1, 1, 1);
	v[7] = D3DXVECTOR3(1, 1, 1);

	D3DXMATRIX matInv;

	matInv = view * proj;
	D3DXMatrixInverse(&matInv, NULL, &matInv);

	D3DXVec3TransformCoord(&v[0], &v[0], &matInv);
	D3DXVec3TransformCoord(&v[1], &v[1], &matInv);
	D3DXVec3TransformCoord(&v[2], &v[2], &matInv);
	D3DXVec3TransformCoord(&v[3], &v[3], &matInv);
	D3DXVec3TransformCoord(&v[4], &v[4], &matInv);
	D3DXVec3TransformCoord(&v[5], &v[5], &matInv);
	D3DXVec3TransformCoord(&v[6], &v[6], &matInv);
	D3DXVec3TransformCoord(&v[7], &v[7], &matInv);

	//근평면
	D3DXPlaneFromPoints(&m_aPlane[0], &v[1], &v[0], &v[2]);

	//우평면
	D3DXPlaneFromPoints(&m_aPlane[1], &v[5], &v[1], &v[3]);

	//상평면
	D3DXPlaneFromPoints(&m_aPlane[2], &v[3], &v[2], &v[6]);

	//원평면
	D3DXPlaneFromPoints(&m_aPlane[3], &v[4], &v[5], &v[7]);

	//좌평면
	D3DXPlaneFromPoints(&m_aPlane[4], &v[0], &v[4], &v[2]);

	//하평면
	D3DXPlaneFromPoints(&m_aPlane[5], &v[0], &v[1], &v[5]);
}

bool cBuildingObject::CheckSphere(float x, float y, float z, float radius)
{
	for (int i = 0; i < 6; i++)
	{
		if (D3DXPlaneDotCoord(&m_aPlane[i], &D3DXVECTOR3(x, y, z)) > radius)
		{
			return false;
		}
	}
	return true;
}