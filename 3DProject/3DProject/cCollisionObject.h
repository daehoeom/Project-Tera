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
	virtual void OnNotCollision(cCollisionObject* rhs);
	void SetCollider( ICollider* collider );
	std::vector<ICollider*>& GetColliderRepo();

private:
	std::vector<ICollider*> m_collider;
};