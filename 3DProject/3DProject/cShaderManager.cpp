#include "stdafx.h"
#include "cShaderManager.h"


cShaderManager::cShaderManager( )
{
}

cShaderManager::~cShaderManager( )
{
	for ( auto& shaderElem : m_effectMap )
	{
		SAFE_RELEASE( shaderElem.second );
	}
}

LPD3DXEFFECT cShaderManager::GetShader(
	const std::string& shaderPath )
{
	auto iter = m_effectMap.find( shaderPath );
	if ( iter == m_effectMap.end( ) )
	{
		LPD3DXEFFECT ret = NULL;

		LPD3DXBUFFER pError = NULL;
		DWORD dwShaderFlags = 0;

#if _DEBUG
		dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

		D3DXCreateEffectFromFileA( g_pD3DDevice, shaderPath.c_str( ),
			NULL, NULL, dwShaderFlags, NULL, &ret, &pError );

		// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
		// 컴파일 에러를 출력한다.
		if ( !ret && pError )
		{
			int size = pError->GetBufferSize( );
			void *ack = pError->GetBufferPointer( );

			if ( ack )
			{
				char* str = new char[size];
				sprintf( str, ( const char* )ack, size );

				MessageBoxA( GetFocus( ),
					str,
					"WARNING!",
					MB_OK | MB_ICONEXCLAMATION
				);
				
				delete[] str;
			}
		}
		else
		{
			m_effectMap[shaderPath] = ret;
		}

		return ret;
	}
	else
	{
		return iter->second;
	}
}
