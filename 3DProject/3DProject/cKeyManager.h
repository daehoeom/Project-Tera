#pragma once
#include "Singleton.h"

#define KEYMANAGER cKeyManager::Get()
#define KEYMAX 256

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

