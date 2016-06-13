#pragma once
#include "IColliseable.h"


class cBuildingObject :
	public IColliseable
{
public:
	cBuildingObject( const std::wstring& name,
			   const std::string& filePath,
			   ICollider* collider = nullptr );
	virtual ~cBuildingObject( );

public:
	virtual void Render( ) override;
	virtual void Update( ) override;

	virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kObj; }

private:
	std::vector<class cGroup*> m_vecGroup;
};

