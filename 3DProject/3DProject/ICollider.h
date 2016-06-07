#pragma once

enum class eColliderType
{
	kSphere,
	kBox,	// AABB
};

class ICollisionDelegate
{
public:
	//virtual void OnCollisionEnter( ) {}
	virtual void OnCollisionStay( class cCollisionObject* ) {}
	//virtual void OnCollisionLeave( ) {}
};

class cGameObject;

class ICollider
{
public:
	ICollider( );
	virtual ~ICollider( ) = 0 {};

	virtual void Update( ) = 0;
	virtual void PreRender( );
	virtual void Render( ) = 0; // Debug renderer
	virtual void PostRender( );

	virtual void SetPosition(const D3DXVECTOR3& pos) = 0;
	virtual D3DXVECTOR3& GetPosition() = 0;
	virtual const D3DXVECTOR3& GetPosition() const = 0;

	virtual void SetWorld(D3DXMATRIXA16* matWorld) { m_matWorld = *matWorld; }
	virtual D3DXMATRIXA16 GetWorld() { return m_matWorld; }
	virtual void SetLocal(D3DXMATRIXA16* matLocal) { m_matLocal = *matLocal; }
	virtual D3DXMATRIXA16 GetLocal() { return m_matLocal; }
public:
	void SetDebugRender( bool isDebugRender );
	bool IsDebugRender( );

	virtual eColliderType GetColliderType( ) const = 0;

protected:
	bool m_isDebugRender;
	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matLocal;
};

inline void ICollider::SetDebugRender( bool isDebugRender )
{
	m_isDebugRender = isDebugRender;
}

inline bool ICollider::IsDebugRender( )
{
	return m_isDebugRender;
}