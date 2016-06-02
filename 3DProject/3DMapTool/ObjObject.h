#pragma once
#include "cGameObject.h"
#include "cObjLoader.h"
#include "cGroup.h"

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

private:
	std::vector<cGroup*> m_vecGroup;
	cObjLoader m_objLoader;
};

