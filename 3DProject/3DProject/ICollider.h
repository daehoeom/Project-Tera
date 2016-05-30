#pragma once

class ICollisionDelegate
{
public:
	virtual bool OnCollisionEnter( ) = 0;
	virtual bool OnCollisionStay( ) = 0;
	virtual bool OnCollisionLeave( ) = 0;
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
	virtual bool IsCollised( ) const = 0;

protected:
	class GameObject* GetOwner( ) { return m_owner; }

private:
	bool m_isDebugRender;
	class GameObject* m_owner;
};