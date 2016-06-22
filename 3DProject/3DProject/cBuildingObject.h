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

class cGroup;
class cLightObject;
class cObjRenderer :
	public IRenderer
{
public:
	explicit cObjRenderer( const char* objFilePath );
	virtual ~cObjRenderer( );

	virtual void Render( ) override;
	const std::vector<cGroup*>& GetGroupRepo( ) const;

public:
	const D3DXVECTOR3& GetMinVector( ) const;
	const D3DXVECTOR3& GetMaxVector( ) const;

private:
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	LPD3DXEFFECT m_effect;
	std::vector<cGroup*> m_groupRepo;
};

inline const std::vector<cGroup*>& cObjRenderer::GetGroupRepo( ) const
{
	return m_groupRepo;
}

inline const D3DXVECTOR3& cObjRenderer::GetMinVector( ) const
{
	return m_min;
}

inline const D3DXVECTOR3& cObjRenderer::GetMaxVector( ) const
{
	return m_max;
}

class cXRenderer :
	public IRenderer
{
public:
	explicit cXRenderer( const char* xFilePath );
	virtual ~cXRenderer( );

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

inline const D3DXVECTOR3& cXRenderer::GetMinVector( ) const
{
	return m_min;
}

inline const D3DXVECTOR3& cXRenderer::GetMaxVector( ) const
{
	return m_max;
}

inline void cXRenderer::SetMesh(
	ID3DXMesh* mesh )
{
	SAFE_RELEASE( m_mesh );
	m_mesh = mesh;
	this->SetupMinAndMax( );
}

inline ID3DXMesh* cXRenderer::GetMesh( )
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

	IRenderer* GetRenderer( );

public:
	virtual void Render( ) override;
	virtual void Update( ) override;

	virtual void OnCollisionStay( int colliderIndex, cCollisionObject* rhs );
	virtual void OnCollisionEnter( int colliderIndex, cCollisionObject* rhs );
	virtual void OnCollisionEnd( int colliderIndex, cCollisionObject* rhs );

private:
	IRenderer* m_renderer;
	D3DXPLANE	m_aPlane[6];
};

inline IRenderer * cBuildingObject::GetRenderer( )
{
	return m_renderer;
}