#include "stdafx.h"
#include "cHPGaugeBar.h"
#include "cUnitObject.h"
#include "cShaderManager.h"
#include "Console.h"

cHPGaugeBar::cHPGaugeBar( 
	const char* hpGuagePath,
	const char* hpFramePath ) :
	m_hpGuage( new cBillboard3DSprite( hpGuagePath ) ),
	m_hpFrame( new cBillboard3DSprite( hpFramePath )),
	m_owner( nullptr ),
	m_hpShader( cShaderManager::Get( )->GetShader( "Shader/HpGauge.fx" )),
	m_texShader( cShaderManager::Get( )->GetShader( "Shader/TextureRendering.fx" ))
{
}

cHPGaugeBar::~cHPGaugeBar( )
{
	SAFE_DELETE( m_hpGuage );
	SAFE_DELETE( m_hpFrame );
}

void cHPGaugeBar::Update( )
{
	assert( m_owner );
	assert( m_hpGuage );
	assert( m_hpFrame );

	__super::Update( );
	
	auto sumPosition = this->GetPosition( ) + m_owner->GetPosition( );
	auto sumScale = this->GetScale( ) + m_owner->GetScale( );

	m_hpFrame->SetPosition( sumPosition );
	m_hpFrame->SetScale( sumScale );
	m_hpFrame->Update( );

	m_hpGuage->SetPosition( sumPosition );
	m_hpGuage->SetScale( sumScale );
	m_hpGuage->Update( );
}

void cHPGaugeBar::Render( )
{
	assert( m_hpGuage );
	assert( m_hpFrame );

	UINT passNum;
	m_hpShader->SetMatrix( "g_matWorld", &m_hpGuage->GetBillBoardMatrix( ) );
	m_hpShader->SetMatrix( "g_matViewProjection", &cCamera::Get( )->GetViewProjection( ) );
	m_hpShader->SetFloat( "HpRatio", 1 );
	m_hpShader->SetTexture( "DiffuseMap_Tex", m_hpGuage->GetTexture( ) );
	m_hpShader->Begin( &passNum, 0 );
	for ( int i = 0; i < passNum; ++i )
	{
		m_hpShader->BeginPass( i );
		m_hpFrame->Render( );
		m_hpShader->EndPass( );
	}

	m_hpShader->End( );

	m_hpShader->SetMatrix( "g_matWorld", &m_hpGuage->GetBillBoardMatrix( ));
	m_hpShader->SetMatrix( "g_matViewProjection", &cCamera::Get( )->GetViewProjection( ));
	m_hpShader->SetFloat( "HpRatio", (float)m_owner->GetCurrHp( ) / (float)m_owner->GetMaxHp( ));
	m_hpShader->SetTexture( "DiffuseMap_Tex", m_hpGuage->GetTexture( ));
	m_hpShader->Begin( &passNum, 0 );
	for ( int i = 0; i < passNum; ++i )
	{
		m_hpShader->BeginPass( i );
		m_hpGuage->Render( );
		m_hpShader->EndPass( );
	}

	m_hpShader->End( );
}
