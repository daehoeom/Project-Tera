#pragma once

class cBuildingObject;
class cLightObject;
class DesertScenePlane
{
public:
	explicit DesertScenePlane( const char* objName );
	~DesertScenePlane( );

	void Render( );
	void Update( );

private:
	cBuildingObject* m_owner;
	LPD3DXEFFECT m_normalMappingShader;
	LPDIRECT3DTEXTURE9 m_diffuseMap;
	LPDIRECT3DTEXTURE9 m_specularMap;
	LPDIRECT3DTEXTURE9 m_normalMap;

	float		m_fHeightY;
};

