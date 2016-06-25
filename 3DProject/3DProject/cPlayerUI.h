#pragma once

class cInventory;
class cEquipWindow;
class cPlayerGauge;
class cPlayerSkill;

class cPlayerUI
{
	cInventory*	m_pInven;
	cPlayerSkill*	m_pSkill;

	SYNTHESIZE(cEquipWindow*, m_pEquip, EquipState);
	SYNTHESIZE(cPlayerGauge*, m_pGauge, Gauge);
public:
	cPlayerUI();
	~cPlayerUI();

	void Update();
	void Render();
};

