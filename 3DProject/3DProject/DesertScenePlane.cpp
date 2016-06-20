#include "stdafx.h"
#include "DesertScenePlane.h"
#include "Console.h"
#include "cGroup.h"
#include "cShaderManager.h"
#include "cLightObject.h"
#include "cBuildingObject.h"

DesertScenePlane::DesertScenePlane( const char* objName ) :
	m_diffuseMap( nullptr ),
	m_specularMap( nullptr ),
	m_normalMap( nullptr ),
	m_normalMappingShader( nullptr ),
	m_fHeightY(0.f),
	m_owner( static_cast<cBuildingObject*>( 
		cGameObjectManager::Get( )->FindObject( objName )))
{
	assert( m_owner );

	m_owner->SetActive( false );
	
	m_normalMappingShader = cShaderManager::Get( )->
		GetShader( "Shader/NormalMapping.fx" );
	
	m_diffuseMap = cTextureManager::Get( )->GetTexture(
		"C:/Users/ggomdyu/Desktop/obj/Desert/sand_tex.jpg" );
	m_specularMap = cTextureManager::Get( )->GetTexture(
		"C:/Users/ggomdyu/Desktop/obj/Desert/sand02c_color_spec.jpg" );
	m_normalMap = cTextureManager::Get( )->GetTexture(
		"C:/Users/ggomdyu/Desktop/obj/Desert/sand02c_color_nrm.jpg" );
}

DesertScenePlane::~DesertScenePlane( )
{
	SAFE_RELEASE(m_normalMappingShader);
	SAFE_RELEASE(m_diffuseMap);
	SAFE_RELEASE(m_specularMap);
	SAFE_RELEASE(m_normalMap);
}

void DesertScenePlane::Render( )
{
	// 뷰 행렬을 만든다.
	// 월드/뷰/투영행렬을 미리 곱한다.
	D3DXMATRIXA16 matWorldView;
	D3DXMATRIXA16 matWorldViewProjection;
	D3DXMatrixMultiply( &matWorldView, &m_owner->GetWorld( ), &cCamera::Get( )->GetView( ) );
	D3DXMatrixMultiply( &matWorldViewProjection, &matWorldView, &cCamera::Get( )->GetProjection( ) );

	m_normalMappingShader->SetTechnique( "NormalMapping" );

	// 쉐이더 전역변수들을 설정
	m_normalMappingShader->SetMatrix( "gWorldMatrix", &m_owner->GetWorld( ) );
	m_normalMappingShader->SetMatrix( "gWorldViewProjectionMatrix", &matWorldViewProjection );

	m_normalMappingShader->SetVector( "gWorldLightPosition",
		&D3DXVECTOR4( g_lightObject->GetPosition( ), 1.f ) );
	m_normalMappingShader->SetVector( "gWorldCameraPosition", &D3DXVECTOR4( cCamera::Get( )->GetEye( ), 1.f ) );

	m_normalMappingShader->SetVector( "gLightColor",
		&g_lightObject->GetLightColor( ) );
	m_normalMappingShader->SetTexture( "DiffuseMap_Tex", m_diffuseMap );
	m_normalMappingShader->SetTexture( "SpecularMap_Tex", m_specularMap );
	m_normalMappingShader->SetTexture( "NormalMap_Tex", m_normalMap );

	// 쉐이더를 시작한다.
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

void DesertScenePlane::Update( )
{
	if ( m_owner )
	{
		m_owner->Update( );
	}

	const auto& groupRepo = static_cast<cObjRenderer*>( m_owner->GetRenderer( ))
		->GetGroupRepo( );

	BOOL collised = FALSE;
	float hitDist = 0.f;
	bool drawn = false;

	for ( auto* groupElem : groupRepo )
	{
		if ( collised == TRUE )
		{
			break;
		}

		const auto& vertices = groupElem->GetVertex( );
		
		for ( int i = 0; i < vertices.size( ); i += 3 )
		{
			const float rayYPos = 10000.f;
			D3DXVECTOR3 rayPos( g_player->GetPosition( ).x, rayYPos,
				g_player->GetPosition( ).z );

			D3DXVECTOR3 v1;
			D3DXVec3TransformCoord( &v1, &vertices[i].p, &m_owner->GetWorld( ));
			D3DXVECTOR3 v2;
			D3DXVec3TransformCoord( &v2, &vertices[i+1].p, &m_owner->GetWorld( ) );
			D3DXVECTOR3 v3;
			D3DXVec3TransformCoord( &v3, &vertices[i+2].p, &m_owner->GetWorld( ) );

			collised = D3DXIntersectTri(
				&v1,
				&v2,
				&v3,
				&rayPos,
				&D3DXVECTOR3( 0.f, -1.f, 0.f ),
				nullptr,
				nullptr,
				&hitDist
			);

			if ( collised == TRUE )
			{
				g_player->GetPosition( ).y = rayYPos - hitDist;
				m_fHeightY = rayYPos - hitDist;
				break;
			}
		}
	}
}
