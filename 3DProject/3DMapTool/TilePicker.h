#pragma once
#include "IPicker.h"

class TilePicker : 
	public IPicker
{
public:
	explicit TilePicker( float size );
	virtual ~TilePicker( );

	virtual bool IsPicked( OUT D3DXVECTOR3* outPickPos );
	virtual PickType GetPickerType( ) const;

public:
	std::vector<D3DXVECTOR3> m_vertexRepo;
	std::vector<uint32_t> m_indexRepo;
};