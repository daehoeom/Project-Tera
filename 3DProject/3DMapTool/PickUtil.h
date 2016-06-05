#pragma once

ST_RAY CalcRay( float x, float y );

void TransformRay( ST_RAY* ray, D3DXMATRIX* mat );

bool RaySphereIntersect( const ST_RAY& ray, const ST_SPHERE& sphere );