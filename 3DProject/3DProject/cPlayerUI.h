#pragma once

class cInventory;
class cEquipWindow;

class cPlayerUI
{
	cInventory*	m_pInven;
	SYNTHESIZE(cEquipWindow*, m_pEquip, EquipState);

public:
	cPlayerUI();
	~cPlayerUI();

	void Update();
	void Render();
};

