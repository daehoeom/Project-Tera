#pragma once

class cGrid;
class cSkinnedMesh;
class cParticle_Firework;
class cSkyBox;

class cMainGame
{
	cGrid*					m_pGrid;	//그리드
	cSkyBox*				m_pSkyBox;	//스카이박스

public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

