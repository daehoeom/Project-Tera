#pragma once

#define KEYMANAGER cKeyManager::GetInstance()
#define KEYMAX 256

class cKeyManager
{
	SINGLETONE(cKeyManager);

private:
	std::bitset<KEYMAX> _keyDown;
	std::bitset<KEYMAX>	_keyUp;
public:

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	std::bitset<KEYMAX> getKeyDown(void) { return _keyDown; }
	std::bitset<KEYMAX> getKeyUp(void) { return _keyUp; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
};

