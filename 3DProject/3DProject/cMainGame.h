#pragma once

class cGrid;
class cSkinnedMesh;
class cParticle_Firework;

class cMainGame
{
	cGrid*			m_pGrid;
	cParticle_Firework* m_pFire;
public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

