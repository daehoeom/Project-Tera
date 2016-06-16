#pragma once
#include "IRenderer.h"

class ObjRenderer :
	public IRenderer
{
public:
	explicit ObjRenderer( const char* objFilePath );
	virtual ~ObjRenderer( );

	virtual void Render( );

public:
	const D3DXVECTOR3& GetMinVector( ) const;
	const D3DXVECTOR3& GetMaxVector( ) const;

private:
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	std::vector<class cGroup*> m_groupRepo;
};

inline const D3DXVECTOR3& ObjRenderer::GetMinVector( ) const
{
	return m_min;
}

inline const D3DXVECTOR3& ObjRenderer::GetMaxVector( ) const
{
	return m_max;
}