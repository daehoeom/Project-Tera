#pragma once
#include "cGameObject.h"


class ICollider;
class cCollisionObject : 
	public cGameObject
{
public:
	cCollisionObject( const std::string& objName );
	virtual ~cCollisionObject( );

	virtual void Update( ) override;
	virtual void Render( ) override;

	void SetCollider( ICollider* collider );
	const std::unique_ptr<ICollider>& GetCollider( );

private:
	std::unique_ptr<ICollider> m_collider;
};