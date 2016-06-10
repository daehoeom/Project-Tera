#pragma once
class cLoadImage : public cGameObject
{

public:
	cLoadImage();
	virtual ~cLoadImage();

	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

protected:
	D3DXMATRIXA16 m_matWorld;
	SYNTHESIZE(ST_SIZE, m_stSize, Size);
	SYNTHESIZE(bool, m_isDebugRender, DebugRender);

};

