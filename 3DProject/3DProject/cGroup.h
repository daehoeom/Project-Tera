#pragma once

#include "cMtlTex.h"

class cGameObject;
class cLightObject;
class cGroup
{
	using _VerticesTy = std::vector<ST_PNT_VERTEX>;

public:
	void Render();

	void SetVertex( const _VerticesTy& vertex );
	const _VerticesTy& GetVertex( );

	SYNTHESIZE_ADD_REF( cMtlTex*, m_pMtlTex, MtlTex );
	SYNTHESIZE( D3DXMATRIX, m_matWorld, World );

public:
	cGroup( void );
	virtual ~cGroup( void );

private:
	_VerticesTy m_vertices;
};

inline void cGroup::SetVertex( const _VerticesTy& vertices )
{
	m_vertices = vertices;
}

inline const cGroup::_VerticesTy& cGroup::GetVertex( )
{
	return m_vertices;
}
