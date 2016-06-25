#pragma once

class cUIObject;

class cPlayerSkill
{
	cUIObject* m_pSkill;
	LPD3DXSPRITE m_pSprite;

public:
	cPlayerSkill();
	~cPlayerSkill();

	void Update();
	void Render();
};

