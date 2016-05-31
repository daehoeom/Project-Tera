#pragma once
#include "cGameObject.h"
#include "ICollider.h"

class cCollisionObject : 
	public cGameObject,
	public ICollisionDelegate
{
public:
	cCollisionObject( const std::string& objName );
	virtual ~cCollisionObject( );

	virtual void Update( ) override;
	virtual void Render( ) override;
	virtual void OnCollisionStay( cCollisionObject* rhs );

	void SetCollider( ICollider* collider );
	const std::unique_ptr<ICollider>& GetCollider( );

private:
	std::unique_ptr<ICollider> m_collider;
};