#include "stdafx.h"
#include "TilePicker.h"

#include "PickUtil.h"
#include "cDeviceManager.h"


TilePicker::TilePicker( float size )
{
	const float elapsed = size / 2;

	m_vertexRepo.resize( 4 );
	m_vertexRepo[0] = { -elapsed, 0.f, -elapsed };
	m_vertexRepo[1] = { -elapsed, 0.f, elapsed };
	m_vertexRepo[2] = { elapsed, 0.f, -elapsed };
	m_vertexRepo[3] = { elapsed, 0.f, elapsed };

	m_indexRepo.resize( 6 );
	m_indexRepo[0] = 0;
	m_indexRepo[1] = 1;
	m_indexRepo[2] = 2;
	m_indexRepo[3] = 2;
	m_indexRepo[4] = 1;
	m_indexRepo[5] = 3;
}

TilePicker::~TilePicker( )
{
}

bool TilePicker::IsPicked( OUT D3DXVECTOR3* outPickPos )
{
	POINT pt;
	GetCursorPos( &pt );
	ScreenToClient( GetFocus( ), &pt );
	ST_RAY ray = CalcRayFromScreenPoint( pt.x, pt.y );

	D3DXMATRIX matView;
	g_pD3DDevice->GetTransform( D3DTS_VIEW, &matView );
	D3DXMATRIX matViewInverse;
	D3DXMatrixInverse( &matViewInverse, nullptr, &matView );
	TransformRay( &ray, &matViewInverse );

	float dist = 0.f;
	BOOL isPicked = false;

	for ( int i = 0; i < m_vertexRepo.size( ); i += 3 )
	{
		isPicked = D3DXIntersectTri(
			&m_vertexRepo[m_indexRepo[i]],
			&m_vertexRepo[m_indexRepo[i+1]],
			&m_vertexRepo[m_indexRepo[i+2]],
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
	}

	*outPickPos = ray.origin + dist*ray.direction;
	return isPicked;
}

PickType TilePicker::GetPickerType( ) const
{
	return PickType::Tile;
}
