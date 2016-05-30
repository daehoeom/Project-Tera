#pragma once

class cGrid;
class cSkinnedMesh;
class cParticle_Firework;
class cSkyBox;

class cMainGame
{
	cGrid*			m_pGrid;
	cParticle_Firework* m_pFire;
	cSkinnedMesh*	m_pBody;
	cSkinnedMesh*   m_pHead;
	cSkyBox*		m_pSkyBox;

public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

