#pragma once
class cCommandCombo
{
public:
	cCommandCombo();
	~cCommandCombo();

	void Input(float InputKey);
	void Destroy();
	void Update();

	std::vector<float> GetCommand() { return m_vecCommand; }
private:
	std::vector<float> m_vecCommand;
	float m_fCommandTime;
	float m_fCommandClear;

};

