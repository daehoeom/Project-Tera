#pragma once

class cUIObject;

class cPlayerGauge
{
	float m_fEnergyWidth;
	float m_fManaWidth;

	cUIObject* m_pHpFrame;
	cUIObject* m_pManaFrame;

	LPD3DXSPRITE m_pSprite;
public:
	cPlayerGauge();
	~cPlayerGauge();

	void Update();
	void Render();

	void SetEnergy(int width);
	void SetMana(int width);
};

