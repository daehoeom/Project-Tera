#pragma once
class cRandomUtil
{
public:
	static void Setup();

	static int GetInteger(int max = 0, int min = 0);
	static float GetFloat(float max = 0.f, float min = 0.f);
	static void GetVector(D3DXVECTOR3& out, D3DXVECTOR3& max, D3DXVECTOR3& min);

private:
	cRandomUtil() = delete;
	~cRandomUtil() = delete;
};

