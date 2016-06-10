#include "StdAfx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"
#include "cTextureManager.h"
#include "StringUtil.h"

#pragma warning( disable: 4996 )


cObjLoader::cObjLoader(void) :
	m_vMin({ std::numeric_limits<float>::max( )-1,
		std::numeric_limits<float>::max( )-1,
		std::numeric_limits<float>::max( )-1}),
	m_vMax({ std::numeric_limits<float>::min( )+1,
		std::numeric_limits<float>::min( )+1,
		std::numeric_limits<float>::min( )+1})
{
}

cObjLoader::~cObjLoader(void)
{
}

void cObjLoader::Load(
	const char* szFullPath, 
	std::vector<cGroup*>& vecGroup )
{
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;
	std::vector<ST_PNT_VERTEX> vecVertex;
	std::string sMtlName;

	FILE* fp = NULL;
	fopen_s(&fp, szFullPath, "r");
	
	if ( !fp )
	{
		MessageBox( 
			GetFocus( ),
			"obj 파일이 존재하지 않습니다.",
			"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
		return;
	}

	auto EndGroupFunc = [&]( )
	{
		if ( !vecVertex.empty( ))
		{
			cGroup* pGroup = new cGroup;
			pGroup->SetMtlTex( m_mapMtlTex[sMtlName] );
			pGroup->SetVertex( vecVertex );
			vecGroup.push_back( pGroup );

			vecVertex.clear( );
		}
	};

	bool isGroupStart = false;
	while ( !feof( fp ))
	{
		char szBuf[1024] = { '\0', };
		fgets(szBuf, 1024, fp);

		if ( strlen( szBuf ) == 0 )
			continue;

		//OutputDebugString(szBuf);
		
		if ( szBuf[0] == '#' ||
			szBuf[0] == '\n' )
		{
			// If created a group, end it
			if ( isGroupStart )
			{
				EndGroupFunc( );
				isGroupStart = false;
			}
		}
		else if (szBuf[0] == 'm')
		{
			std::string szMtlPath;
			szMtlPath.resize( 1024 );
			sscanf( szBuf, "%*s %s", &szMtlPath[0] );

			szMtlPath = 
				GetPathWithoutFileName( szFullPath ) +
				GetFileNameFromPath( szMtlPath );

			LoadMtlLib( szMtlPath.c_str( ) );
		}
		else if (szBuf[0] == 'g')
		{
			if ( isGroupStart )
			{
				EndGroupFunc( );
				//isGroupStart = false;
			}
			isGroupStart = true;
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't')
			{
				float u, v;
				sscanf(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf(szBuf, "%*s %f %f %f", &x, &y, &z);

				m_vMin.x = std::min( m_vMin.x, x );
				m_vMin.y = std::min( m_vMin.y, y );
				m_vMin.z = std::min( m_vMin.z, z );
				
				m_vMax.x = std::max( m_vMax.x, x );
				m_vMax.y = std::max( m_vMax.y, y );
				m_vMax.z = std::max( m_vMax.z, z );

				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf(szBuf, "%*s %s", szMtlName);
			sMtlName = std::string(szMtlName);
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);
			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
		}
	}

	for (auto& it : m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}

	fclose(fp);
}

void cObjLoader::LoadMtlLib(
	const char* szFullPath)
{
	FILE* fp = NULL;
	fopen_s(&fp, szFullPath, "r");

	if ( !fp )
	{
		std::string errMsg = 
			std::string( "알 수 없는 메테리얼 경로가 발견되었습니다. ( " ) +
			std::string( szFullPath ) + 
			std::string( " )" );

		MessageBoxA(
			GetFocus( ),
			errMsg.c_str( ),
			"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
	}

	std::string sMtlName;

	while (true)
	{
		char szBuf[1024] = { '\0', };
		fgets(szBuf, 1024, fp);

		if (feof(fp))
			break;

		if (strlen(szBuf) == 0)
			continue;

		//OutputDebugString(szBuf);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf(szBuf, "%*s %s", szMtlName);
			sMtlName = std::string(szMtlName);
			SAFE_RELEASE(m_mapMtlTex[sMtlName]);
			m_mapMtlTex[sMtlName] = new cMtlTex;
		}
		else if (szBuf[0] == 'K' || 
			szBuf[1] == 'K' )
		{
			if (szBuf[1] == 'a' ||
				szBuf[2] == 'a' )
			{
				float r, g, b;
				sscanf(szBuf, "%*s %f %f %f", &r, &g, &b);

				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Ambient.r = r;
				stMtl.Ambient.g = g;
				stMtl.Ambient.b = b;
				stMtl.Ambient.a = 1.0f;
			}
			else if (szBuf[1] == 'd' ||
				szBuf[2] == 'd' )
			{
				float r, g, b;
				sscanf(szBuf, "%*s %f %f %f", &r, &g, &b);

				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Diffuse.r = r;
				stMtl.Diffuse.g = g;
				stMtl.Diffuse.b = b;
				stMtl.Diffuse.a = 1.0f;
			}
			else if (szBuf[1] == 's' ||
				szBuf[2] == 's' )
			{
				float r, g, b;
				sscanf(szBuf, "%*s %f %f %f", &r, &g, &b);

				D3DMATERIAL9& stMtl = m_mapMtlTex[sMtlName]->GetMtl();
				stMtl.Specular.r = r;
				stMtl.Specular.g = g;
				stMtl.Specular.b = b;
				stMtl.Specular.a = 1.0f;
			}
		}
		else if ( strstr( szBuf, "map_Kd" ))
		{
			std::string szTexPath;
			szTexPath.resize( 1024, '\0' );
			sscanf( szBuf, "%*s %s", &szTexPath[0] );

			szTexPath =
				GetPathWithoutFileName( szFullPath ) +
				GetFileNameFromPath( szTexPath );

			LPDIRECT3DTEXTURE9 pTexture = NULL;
			pTexture = g_pTextureManager->GetTexture( szTexPath );

			m_mapMtlTex[sMtlName]->SetTexture( pTexture );
		}
	}

	fclose(fp);
}