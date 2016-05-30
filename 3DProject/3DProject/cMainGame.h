#pragma once
#include "cBoundingBox.h"

class cGrid;
class cSkinnedMesh;
class cParticle_Firework;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	cBoundingBox boundingBox1;
	//cBoundingBox boundingBox2;

	cGrid*			m_pGrid;
	cParticle_Firework* m_pFire;
	cSkinnedMesh*	m_pBody;
	cSkinnedMesh*   m_pHead;
};

