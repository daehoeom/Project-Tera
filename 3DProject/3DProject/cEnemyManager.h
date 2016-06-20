#pragma once

class cEnemy;

class cEnemyManager 
	: public cGameObject
{
	std::vector<cEnemy*> m_vecEnemy;
public:
	cEnemyManager();
	~cEnemyManager();

	void Update();
	void Render();
};

