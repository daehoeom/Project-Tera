#pragma once
#include "cCollisionObject.h"


class ObjObject :
	public cCollisionObject
{
public:
	ObjObject( const std::string& name,
			   const std::string& filePath,
			   ICollider* collider = nullptr );
	virtual ~ObjObject( );

public:
	virtual void Render( ) override;
	virtual void Update( ) override;

	//virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kObj; }

private:
	std::vector<class cGroup*> m_vecGroup;
};

