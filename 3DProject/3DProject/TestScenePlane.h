#pragma once
#include "cGameObject.h"

class TestScenePlane
{
public:
	explicit TestScenePlane( const char* objName );
	virtual ~TestScenePlane( );

	void Render( );
	void Update( );

private:
	cGameObject* m_owner;
	LPD3DXEFFECT gpNormalMappingShader;
	LPDIRECT3DTEXTURE9 gpStoneDM;
	LPDIRECT3DTEXTURE9 gpStoneSM;
	LPDIRECT3DTEXTURE9 gpStoneNM;
};
