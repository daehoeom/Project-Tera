#pragma once

class IRenderer
{
public:
	IRenderer( ) {};
	virtual ~IRenderer( ) = 0 {};

	virtual void Render( ) = 0;

public:
	void SetOwner( class cGameObject* );
	class cGameObject* GetOwner( );

private:
	class cGameObject* m_owner;
};

inline void IRenderer::SetOwner(
	cGameObject* owner )
{
	m_owner = owner;
}

inline cGameObject* IRenderer::GetOwner( )
{
	return m_owner;
}


class ObjRenderer :
	public IRenderer
{
public:
	explicit ObjRenderer( const char* objFilePath );
	virtual ~ObjRenderer( );

	virtual void Render( ) override;

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

inline const D3DXVECTOR3& XRenderer::GetMinVector( ) const
{
	return m_min;
}

inline const D3DXVECTOR3& XRenderer::GetMaxVector( ) const
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

inline ID3DXMesh* XRenderer::GetMesh( )
{
	return m_mesh;
}

class cObjLoader;
class cGroup;
class cBuildingObject :
	public cCollisionObject
{
public:
	explicit cBuildingObject( const std::string& modelFilePath );
	virtual ~cBuildingObject( );

public:
	virtual void Render( ) override;
	virtual void Update( ) override;

	virtual void OnCollisionStay( int colliderIndex, cCollisionObject* rhs );
	virtual void OnCollisionEnter( int colliderIndex, cCollisionObject* rhs );
	virtual void OnCollisionEnd( int colliderIndex, cCollisionObject* rhs );

private:
	IRenderer* m_renderer;
};