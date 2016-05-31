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
	ICollider( cGameObject* owner );
	virtual ~ICollider( ) = 0 {};

	virtual void Update( ) = 0;
	virtual void PreRender( );
	virtual void Render( ) = 0; // Debug renderer
	virtual void PostRender( );

public:
	void SetDebugRender( bool isDebugRender );
	bool IsDebugRender( );

	virtual eColliderType GetColliderType( ) const = 0;

	void SetOwner( cGameObject* owner );
	cGameObject* GetOwner( );
	const cGameObject* GetOwner( ) const;

private:
	bool m_isDebugRender;
	class cGameObject* m_owner;
};

inline void ICollider::SetDebugRender( bool isDebugRender )
{
	m_isDebugRender = isDebugRender;
}

inline bool ICollider::IsDebugRender( )
{
	return m_isDebugRender;
}

inline void ICollider::SetOwner( cGameObject * owner )
{
	m_owner = owner;
}

inline cGameObject * ICollider::GetOwner( )
{
	return m_owner;
}

inline const cGameObject * ICollider::GetOwner( ) const
{
	return m_owner;
}
