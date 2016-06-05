#pragma once
#include "IPickable.h"
#include "cObjLoader.h"
#include "cGroup.h"


class ObjObject : 
	public IPickable
{
public:
	ObjObject( const std::wstring& name,
			   const std::string& filePath );
	virtual ~ObjObject( );

public:
	virtual void Render( ) override;
	virtual void Update( ) override;

	virtual ObjectIdenfier GetIdenfier( ) const override { return ObjectIdenfier::kObject; }
	virtual bool IsPicked( const D3DXVECTOR3& pickedPos ) const override;

private:
	std::vector<cGroup*> m_vecGroup;
};

