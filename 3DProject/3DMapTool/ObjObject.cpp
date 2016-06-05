#include "stdafx.h"
#include "ObjObject.h"

#include "PickUtil.h"
#include "cDeviceManager.h"

ObjObject::ObjObject( 
	const std::wstring& name,
	const std::string& filePath ) :
	IPickable( name )
{
	cObjLoader objLoader;
	objLoader.Load( filePath.c_str(), m_vecGroup, nullptr );

//	d3dxinterse

	float radius = objLoader.GetMaxVector( ).x -
		objLoader.GetMinVector( ).x;
}

ObjObject::~ObjObject( )
{
	for each( auto p in m_vecGroup )
	{
		SAFE_RELEASE( p );
	}
	m_vecGroup.clear( );
}

void ObjObject::Render( )
{
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &this->GetWorld( ));

	for ( auto& p : m_vecGroup )
	{
		p->Render( );
	}
}

void ObjObject::Update( )
{
}

bool ObjObject::IsPicked( const D3DXVECTOR3& pickedPos ) const
{
	POINT pt;
	GetCursorPos( &pt );
	ScreenToClient( GetFocus( ), &pt );
	ST_RAY ray = CalcRay( pt.x, pt.y );

	D3DXMATRIX matView;
	g_pD3DDevice->GetTransform( D3DTS_VIEW, &matView );
	D3DXMATRIX matViewInverse;
	D3DXMatrixInverse( &matViewInverse, nullptr, &matView );
	TransformRay( &ray, &matViewInverse );

	float dist = 0.f;
	BOOL isPicked = false;

	/*for ( int i = 0; i < m_indexCache.size( ); i += 3 )
	{
		isPicked = D3DXIntersectTri(
			&m_vertexCache[m_indexCache[i]].p,
			&m_vertexCache[m_indexCache[i + 1]].p,
			&m_vertexCache[m_indexCache[i + 2]].p,
			&ray.origin,
			&ray.direction,
			nullptr,
			nullptr,
			&dist
		);

		if ( isPicked )
		{
			break;
		}
	}*/

	return ( isPicked ) ? true : false;
}
