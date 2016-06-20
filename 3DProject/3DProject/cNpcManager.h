#pragma once

class cNpc;

class cNpcManager 
	: public cGameObject
{
	std::vector<cNpc*>	m_vecNpc;
public:
	cNpcManager();
	~cNpcManager();

	std::vector<cNpc*> GetNpc() { return m_vecNpc; }

	void Update();
	void Render();
};

