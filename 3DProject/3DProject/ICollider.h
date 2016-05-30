#pragma once

class ICollisionDelegate
{
public:
	virtual void OnCollisionEnter( ) {}
	virtual void OnCollisionStay( ) {}
	virtual void OnCollisionLeave( ) {}
};

class ICollider
{
public:
	ICollider( class GameObject* owner );
	virtual ~ICollider( ) = 0 {};

	virtual void Update( ) = 0;
	virtual void PreRender( );
	virtual void Render( ) = 0; // Debug renderer
	virtual void PostRender( );

public:
	void SetDebugRender( bool isDebugRender );
	bool IsDebugRender( );

	void SetOwner( class GameObject* owner );
	class GameObject* GetOwner( );

private:
	bool m_isDebugRender;
	class GameObject* m_owner;
};

inline void ICollider::SetDebugRender( bool isDebugRender )
{
	m_isDebugRender = isDebugRender;
}

inline bool ICollider::IsDebugRender( )
{
	return m_isDebugRender;
}

inline void ICollider::SetOwner( GameObject * owner )
{
	m_owner = owner;
}

inline GameObject * ICollider::GetOwner( )
{
	return m_owner;
}
