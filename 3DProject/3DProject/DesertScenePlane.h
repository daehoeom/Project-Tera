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

	float GetHeight() { return m_fHeightY; }

private:
	cBuildingObject* m_owner;
	LPD3DXEFFECT m_fogShader;
	D3DXHANDLE m_fogTechHandle;
	LPDIRECT3DTEXTURE9 m_diffuseMap;
	float		m_fHeightY;

};

