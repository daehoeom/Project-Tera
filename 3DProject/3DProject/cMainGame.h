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

private:
	std::shared_ptr<class cPlayer>		m_player;
	std::shared_ptr<class cGrid>		m_pGrid;
	std::shared_ptr<class cSkyBox>		m_pSkyBox;

};

