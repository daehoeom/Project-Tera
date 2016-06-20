#include "stdafx.h"
#include "TestScenePlane.h"

#include "cShaderManager.h"
#include "cLightObject.h"


TestScenePlane::TestScenePlane( const char* objName ) :
	m_diffuseMap( nullptr ),
	m_specularMap( nullptr ),
	m_normalMap( nullptr ),
	m_normalMappingShader( nullptr ),
	m_owner( cGameObjectManager::Get( )->FindObject( objName ))
{
	assert( m_owner );

	m_owner->SetActive( false );
	
	m_normalMappingShader = cShaderManager::Get( )->
		GetShader( "Shader/NormalMapping.fx" );
	
	m_diffuseMap = cTextureManager::Get( )->GetTexture(
		"Resource/TownScene/Free_Stonewall/StonePlaneDiffuse.jpg" );
	m_specularMap = cTextureManager::Get( )->GetTexture(
		"Resource/TownScene/Free_Stonewall/StonePlaneSpecular.jpg" );
	m_normalMap = cTextureManager::Get( )->GetTexture(
		"Resource/TownScene/Free_Stonewall/StonePlaneNormal.jpg" );
}

TestScenePlane::~TestScenePlane( )
{
}

void TestScenePlane::Render( )
{
	m_normalMappingShader->SetTechnique( "NormalMapping" );


	const D3DXMATRIXA16 matWorldViewProjection =
		m_owner->GetWorld( ) * cCamera::Get( )->GetViewProjection( );

	// Global variable setting
	m_normalMappingShader->SetMatrix( "gWorldMatrix", &m_owner->GetWorld( ));
	m_normalMappingShader->SetMatrix( "gWorldViewProjectionMatrix", &matWorldViewProjection );
	m_normalMappingShader->SetVector( "gWorldLightPosition",
		&D3DXVECTOR4( g_lightObject->GetPosition( ), 1.f ));
	m_normalMappingShader->SetVector( "gWorldCameraPosition", 
		&D3DXVECTOR4( cCamera::Get( )->GetEye( ), 1.f ));

	m_normalMappingShader->SetVector( "gLightColor", 
		&g_lightObject->GetLightColor( ));
	m_normalMappingShader->SetTexture( "DiffuseMap_Tex", m_diffuseMap );
	m_normalMappingShader->SetTexture( "SpecularMap_Tex", m_specularMap );
	m_normalMappingShader->SetTexture("NormalMap_Tex", m_normalMap );


	UINT numPasses = 0;
	m_normalMappingShader->Begin( &numPasses, NULL );
	{
		for ( UINT i = 0; i < numPasses; ++i )
		{
			m_normalMappingShader->BeginPass( i );
			{
				if ( m_owner )
				{
					m_owner->Render( );
				}
			}
			m_normalMappingShader->EndPass( );
		}
	}
	m_normalMappingShader->End( );
}

void TestScenePlane::Update( )
{
	if ( m_owner )
	{
		m_owner->Update( );
	}
}
