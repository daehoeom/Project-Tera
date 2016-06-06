#pragma once

enum PickType
{
	Sphere,
	Box,
	Tile,
};

class IPicker
{
public:
	IPicker( );
	virtual ~IPicker( ) = 0;

	virtual bool IsPicked( OUT D3DXVECTOR3* outPickPos ) = 0;
	virtual PickType GetPickerType( ) const = 0;
};