#pragma once
#include "IColliseable.h"

class cBuildingObject :
	public IColliseable
{
public:
	explicit cBuildingObject( const std::wstring& name );
	virtual ~cBuildingObject( );

	virtual void Render( ) override;
	virtual void Update( ) override;

public:
	virtual ObjectIdenfier GetIdenfier( ) const override;
};

inline ObjectIdenfier cBuildingObject::GetIdenfier( ) const
{
	return ObjectIdenfier::kBuilding; 
}
