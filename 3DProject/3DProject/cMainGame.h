#pragma once

class cGrid;
class cSkinnedMesh;

class cMainGame
{
	cGrid*			m_pGrid;
	cSkinnedMesh*	m_pMesh;
public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

