#pragma once
#include "IRenderer.h"

class cObjRenderer :
	public IRenderer
{
public:
	explicit cObjRenderer( const char* objFilePath );
	virtual ~cObjRenderer( );

	virtual void Render( );

public:
	const D3DXVECTOR3& GetMinVector( ) const;
	const D3DXVECTOR3& GetMaxVector( ) const;

private:
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	std::vector<class cGroup*> m_groupRepo;
};

inline const D3DXVECTOR3& cObjRenderer::GetMinVector( ) const
{
	return m_min;
}

inline const D3DXVECTOR3& cObjRenderer::GetMaxVector( ) const
{
	return m_max;
}