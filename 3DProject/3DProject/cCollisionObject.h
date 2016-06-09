#pragma once
#include "cGameObject.h"
#include "ICollider.h"

class cCollisionObject : 
	public cGameObject,
	public ICollisionDelegate
{
public:
	explicit cCollisionObject( const std::string& objName );
	virtual ~cCollisionObject( );

	//Check Collision
	void SetCollision(bool collision) { m_bIsCollision = collision; }
	bool GetCollision() { return m_bIsCollision; }
	virtual void Update( ) override;
	virtual void Render( ) override;
	virtual void OnCollisionStay( cCollisionObject* rhs );
	void SetCollider( ICollider* collider );
	std::vector<ICollider*>& GetColliderRepo();

private:
	bool m_bIsCollision;
	std::vector<ICollider*> m_collider;
};