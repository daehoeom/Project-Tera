#pragma once

class cGameObject;
class DesertSceneOasis
{
public:
	DesertSceneOasis( );
	~DesertSceneOasis( );

public:
	void Render( );
	void Update( );

private:
	float m_elapsedTime;
	cGameObject* m_target;
	IDirect3DTexture9* m_diffuseTex;
	IDirect3DTexture9* m_bumpNormalTex;
	ID3DXEffect* m_oasisShader;
};

