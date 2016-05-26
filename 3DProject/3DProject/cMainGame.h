#pragma once

class cCamera;
class cGrid;

class cMainGame
{
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;
public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

