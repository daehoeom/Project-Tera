#pragma once
#include "cPlayer.h"

class cGrid;
class cSkinnedMesh;
class cParticle_Firework;
class cSkyBox;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	cPlayer				m_player;
	cGrid*				m_pGrid;
	cParticle_Firework* m_pFire;
	cSkinnedMesh*		m_pBody;
	cSkinnedMesh*		m_pHead;
	cSkyBox*			m_pSkyBox;
};

