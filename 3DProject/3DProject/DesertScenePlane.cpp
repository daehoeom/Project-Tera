#include "stdafx.h"
#include "DesertScenePlane.h"
#include "Console.h"
#include "cGroup.h"
#include "cShaderManager.h"
#include "cLightObject.h"
#include "cBuildingObject.h"
#include "cShaderManager.h"

DesertScenePlane::DesertScenePlane( ) :
	m_owner( static_cast<cPlaneObject*>( 
		cGameObjectManager::Get( )->FindObject( "Desert_plane0" ))),
	m_fogShader( cShaderManager::Get( )->GetShader( "Shader/fog.fx" ))
{
	assert( m_owner );

	m_owner->SetActive( false );
}

DesertScenePlane::~DesertScenePlane( )
{
}

float DesertScenePlane::GetHeight( 
	cGameObject* target )
{
	const auto& groupRepo = static_cast<cObjRenderer*>( 
		m_owner->GetRenderer( ))->GetGroupRepo( );

	BOOL collised = FALSE;
	float hitDist = 0.f;

	for ( auto* groupElem : groupRepo )
	{
		const auto& vertices = groupElem->GetVertex( );
		
		for ( int i = 0; i < vertices.size( ); i += 3 )
		{
			const float rayYPos = 10000.f;
			D3DXVECTOR3 rayPos( target->GetPosition( ).x, rayYPos,
				target->GetPosition( ).z );

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
				target->GetPosition( ).y = rayYPos - hitDist;
				return ( rayYPos-hitDist );
			}
		}
	}

	return 0.f;
}

void DesertScenePlane::Render( )
{
	m_fogShader->SetTechnique( m_fogTechHandle );

	UINT numPasses = 0;
	m_fogShader->Begin( &numPasses, 0 );
	
	for ( int i = 0; i < numPasses; i++ )
	{
		m_fogShader->BeginPass( i );

		auto groupRepo = static_cast<cObjRenderer*>( m_owner->GetRenderer( ))
			->GetGroupRepo( );

		g_pD3DDevice->SetTransform( D3DTS_WORLD, &m_owner->GetWorld( ) );
		g_pD3DDevice->SetTexture( 0, m_diffuseMap );

		for ( auto groupElem : groupRepo )
		{
			groupElem->Render( );
		}

		m_fogShader->EndPass( );
	}
	m_fogShader->End( );

}

void DesertScenePlane::Update( )
{
}
