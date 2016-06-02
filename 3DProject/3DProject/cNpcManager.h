#pragma once

class cNpc;

class cNpcManager 
{
	std::vector<cNpc*>	m_vecNpc;
public:
	cNpcManager();
	~cNpcManager();

	std::vector<cNpc*> GetNpc() { return m_vecNpc; }

	void Update();
	void Render();
};

