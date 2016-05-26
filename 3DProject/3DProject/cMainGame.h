#pragma once

class cGrid;

class cMainGame
{
	cGrid* m_pGrid;

public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

