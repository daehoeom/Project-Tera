#pragma once
#include "cGameObject.h"


class ObjObject :
	public cGameObject
{
public:
	ObjObject( const std::wstring& name,
			   const std::string& filePath );
	virtual ~ObjObject( );

public:
	virtual void Render( ) override;
	virtual void Update( ) override;

	virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kObject; }

private:
	std::vector<class cGroup*> m_vecGroup;
};

