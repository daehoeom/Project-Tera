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

public:
	void SetDebugRender( bool isDebugRender );
	bool IsDebugRender( );

	virtual eColliderType GetColliderType( ) const = 0;

private:
	bool m_isDebugRender;
};

inline void ICollider::SetDebugRender( bool isDebugRender )
{
	m_isDebugRender = isDebugRender;
}

inline bool ICollider::IsDebugRender( )
{
	return m_isDebugRender;
}