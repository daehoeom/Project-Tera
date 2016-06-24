#pragma once

class cGameObject;
class cPlaneObject;
class cLightObject;
class DesertScenePlane
{
public:
	DesertScenePlane( );
	~DesertScenePlane( );

	void Render( );
	void Update( );

	float GetHeight( cGameObject* );

private:
	cPlaneObject* m_owner;
	LPD3DXEFFECT m_fogShader;
	D3DXHANDLE m_fogTechHandle;
	LPDIRECT3DTEXTURE9 m_diffuseMap;
};

