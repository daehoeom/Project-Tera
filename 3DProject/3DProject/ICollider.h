#pragma once

class ICollisionDelegate
{
public:
	virtual bool OnCollisionEnter( ) { return false; }
	virtual bool OnCollisionStay( ) { return false; }
	virtual bool OnCollisionLeave( ) { return false; }
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

	void SetDebugRender( bool isDebugRender ) { m_isDebugRender = isDebugRender; }
	bool IsDebugRender( ) const { return m_isDebugRender; }

	void SetOwner( class GameObject* owner ) { m_owner = owner; }
	class GameObject* GetOwner( ) { return m_owner; }

private:
	bool m_isDebugRender;
	class GameObject* m_owner;
};