#pragma once
#include "IRenderer.h"

class XRenderer :
	public IRenderer
{
public:
	explicit XRenderer( const char* xFilePath );
	virtual ~XRenderer( );

	virtual void Render( );

public:
	const D3DXVECTOR3& GetMinVector( ) const;
	const D3DXVECTOR3& GetMaxVector( ) const;
	void SetMesh( ID3DXMesh* );
	ID3DXMesh* GetMesh( );

private:
	void SetupMinAndMax( );

private:
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	DWORD m_mtrlCount;
	ID3DXMesh* m_mesh;
};


inline const D3DXVECTOR3 & XRenderer::GetMinVector( ) const
{
	return m_min;
}

inline const D3DXVECTOR3 & XRenderer::GetMaxVector( ) const
{
	return m_max;
}

inline void XRenderer::SetMesh(
	ID3DXMesh* mesh )
{
	SAFE_RELEASE( m_mesh );
	m_mesh = mesh;
	this->SetupMinAndMax( );
}

inline ID3DXMesh * XRenderer::GetMesh( )
{
	return m_mesh;
}