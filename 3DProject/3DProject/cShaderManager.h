#pragma once
#include "Singleton.h"

class cShaderManager :
	public TSingleton<cShaderManager>
{
public:
	LPD3DXEFFECT GetShader( const std::string& shaderPath );
	
protected:
	cShaderManager( );
	virtual ~cShaderManager( );

private:
	std::map<std::string, LPD3DXEFFECT> m_effectMap;
};

