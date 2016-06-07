#pragma once

class cPlayer;
class cGrid;
class cSkyBox;
class cObjLoader;
class cGroup;
class cNpcManager;
class cFatHunter;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void SetupManagers( );

private:
	cGrid*							m_pGrid;
	cSkyBox*						m_pSkyBox;
	cObjLoader*						m_pLoader;
	cNpcManager*					m_pNpc;
	cFatHunter*		m_pMonster;
	std::vector<cGroup*>			m_vecGroup;
};