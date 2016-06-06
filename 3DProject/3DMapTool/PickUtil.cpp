#include "stdafx.h"
#include "PickUtil.h"

#include "cDeviceManager.h"


ST_RAY CalcRayFromScreenPoint( float x, float y )
{
	D3DVIEWPORT9 viewPort;
	g_pD3DDevice->GetViewport( &viewPort );

	D3DXMATRIXA16 matProj;
	g_pD3DDevice->GetTransform( D3DTRANSFORMSTATETYPE::D3DTS_PROJECTION, &matProj );

	const float px = ( ( ( 2.f*x ) / viewPort.Width ) - 1.f ) * ( 1 / matProj( 0, 0 ) );
	const float py = ( ( ( -2.f*y ) / viewPort.Height ) + 1.f ) * ( 1 / matProj( 1, 1 ) );

	ST_RAY ray;
	ray.origin = { 0.f, 0.f, 0.f };
	ray.direction = { px, py, 1.f };

	return ray;
}

void TransformRay( ST_RAY* ray, D3DXMATRIX* mat )
{
	// Transform ray's original point 
	D3DXVec3TransformCoord(
		&ray->origin,
		&ray->origin,
		mat
		);

	// Transform ray's direction
	D3DXVec3TransformNormal(
		&ray->direction,
		&ray->direction,
		mat
		);

	// Normalize the direction.
	D3DXVec3Normalize( &ray->direction, &ray->direction );
}

bool RaySphereIntersect(
	const ST_RAY& ray,
	const ST_SPHERE& sphere )
{
	D3DXVECTOR3 v = ray.origin - sphere.position;

	float b = 2.f * D3DXVec3Dot( &ray.direction, &v );
	float c = D3DXVec3Dot( &v, &v ) - ( sphere.radius * sphere.radius );


	// 정규식을 찾아내자
	float discriminant = ( b*b ) - 4.f*c;
	if ( discriminant < 0.f )
		return false;

	float s0 = ( -b + sqrt( discriminant ) ) / 2.f;
	float s1 = ( -b - sqrt( discriminant ) ) / 2.f;

	if ( s0 >= 0.f || s1 >= 0.f )
		return true;

	return false;
}