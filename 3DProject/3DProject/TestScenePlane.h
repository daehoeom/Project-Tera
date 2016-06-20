#pragma once
#include "cGameObject.h"


class cLightObject;
class TestScenePlane :
	public cGameObject
{
public:
	explicit TestScenePlane( const char* objName );
	virtual ~TestScenePlane( );

	virtual void Render( ) override;
	virtual void Update( ) override;

private:
	cGameObject* m_owner;
	LPD3DXEFFECT m_normalMappingShader;
	LPDIRECT3DTEXTURE9 m_diffuseMap;
	LPDIRECT3DTEXTURE9 m_specularMap;
	LPDIRECT3DTEXTURE9 m_normalMap;
};
