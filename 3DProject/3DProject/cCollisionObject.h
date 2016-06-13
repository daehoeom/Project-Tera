#pragma once
#include "cGameObject.h"
#include "ICollider.h"

class cCollisionObject : 
	public cGameObject,
	public ICollisionDelegate
{
	using _ColliderRepoTy = std::vector<ICollider*>;
	using _HadCollidedRepoTy = std::vector<bool>;

public:
	explicit cCollisionObject( const std::string& objName );
	virtual ~cCollisionObject( );

	virtual void Update( ) override;
	virtual void Render( ) override;
	
	//Check Collision
	void SetCollision( int colliderIndex, bool isCollided );
	bool GetCollision( int colliderIndex ) const;
	virtual void OnCollisionStay( int colliderIndex, cCollisionObject* rhs );
	virtual void OnCollisionEnter( int colliderIndex, cCollisionObject* rhs );
	virtual void OnCollisionEnd( int colliderIndex, cCollisionObject* rhs );
	void AddCollider( ICollider* collider );
	const _ColliderRepoTy& GetColliderRepo( ) const;

private:
	_HadCollidedRepoTy m_collidedRepo;
	_ColliderRepoTy m_colliderRepo;
};


inline void cCollisionObject::SetCollision( 
	int colliderIndex, 
	bool isCollided )
{
	m_collidedRepo[colliderIndex] = isCollided;
}

inline bool cCollisionObject::GetCollision( int colliderIndex ) const
{
	return m_collidedRepo[colliderIndex];
}

inline const cCollisionObject::_ColliderRepoTy& 
	cCollisionObject::GetColliderRepo( ) const
{
	return m_colliderRepo;
}