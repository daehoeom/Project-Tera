#pragma once
#include "Singleton.h"

#define KEYMANAGER cKeyManager::Get()
#define KEYMAX 256

enum VIRTUAL
{
	VK_A = 0x41,
	VK_B,
	VK_C,
	VK_D,
	VK_E,
	VK_F,
	VK_G,
	VK_H,
	VK_I,
	VK_J,
	VK_K,
	VK_L,
	VK_M,
	VK_N,
	VK_O,
	VK_P,
	VK_Q,
	VK_R,
	VK_S,
	VK_T,
	VK_U,
	VK_V,
	VK_W,
	VK_X,
	VK_Y,
	VK_Z,
};

class cKeyManager :
	public TSingleton<cKeyManager>
{
public:

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	std::bitset<KEYMAX> getKeyDown(void) { return _keyDown; }
	std::bitset<KEYMAX> getKeyUp(void) { return _keyUp; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

protected:
	cKeyManager( );
	virtual ~cKeyManager( );

private:
	std::bitset<KEYMAX> _keyDown;
	std::bitset<KEYMAX>	_keyUp;
};

