#include "stdafx.h"
#include "DesertSceneOasis.h"

#include "cGameObjectManager.h"
#include "cShaderManager.h"
#include "cTextureManager.h"
#include "cTimeManager.h"

DesertSceneOasis::DesertSceneOasis( ) :
	m_target( cGameObjectManager::Get( )->FindObject( "OasisPool0" )),
	m_diffuseTex( cTextureManager::Get( )->GetTexture( "Resource/DesertScene/Pool/water.jpg" )),
	m_bumpNormalTex( cTextureManager::Get( )->GetTexture( "Resource/DesertScene/Pool/bumpnoisesemi64.tga" )),
	m_oasisShader( cShaderManager::Get( )->GetShader( "Shader/WaterFalling.fx" )),
	m_elapsedTime( 0.f )
{
	assert( m_target );

	m_target->SetActive( false );
}

DesertSceneOasis::~DesertSceneOasis( )
{
}

void DesertSceneOasis::Render( )
{
	assert( m_target );


	m_elapsedTime += cTimeManager::Get( )->GetDeltaTime( );


	HRESULT result = FALSE;
	result = m_oasisShader->SetFloat( "fTime0_X", m_elapsedTime );
	assert( result == S_OK );
	result = m_oasisShader->SetMatrix( "g_matWorld", &m_target->GetWorld( ));
	assert( result == S_OK );
	result = m_oasisShader->SetMatrix( "g_matViewProjection", &cCamera::Get()->GetViewProjection( ) );
	assert( result == S_OK );
	result = m_oasisShader->SetTexture( "diffuse_Tex", m_diffuseTex );
	assert( result == S_OK );
	result = m_oasisShader->SetTexture( "bump_Tex", m_bumpNormalTex );
	assert( result == S_OK );

	UINT passNum;
	m_oasisShader->Begin( &passNum, 0 );

	for ( int i = 0; i < passNum; ++i )
	{
		m_oasisShader->BeginPass( i );
		if ( m_target )
		{
			m_target->Render( );
		}
		m_oasisShader->EndPass( );
	}

	m_oasisShader->End( );
}

void DesertSceneOasis::Update( )
{
	if ( m_target )
	{
		m_target->Update( );
	}
}
