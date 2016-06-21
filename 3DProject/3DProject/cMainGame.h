#pragma once

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

	LPD3DXFONT		m_pFont;

	float			m_fFrameTime;
	DWORD			m_dwFrameCount;
	DWORD			m_dwFrameRate;
};