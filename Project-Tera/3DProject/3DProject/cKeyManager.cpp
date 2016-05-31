#include "stdafx.h"
#include "cKeyManager.h"


cKeyManager::cKeyManager()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyDown.set(i, false);
		_keyUp.set(i, false);
	}
}


cKeyManager::~cKeyManager()
{
}

bool cKeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown.set(key, true);
			return true;
		}
	}

	else
		_keyDown.set(key, false);

	return false;
}

bool cKeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		_keyUp.set(key, true);

	else
	{
		if (_keyUp[key])
		{
			_keyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool cKeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	else
		return false;
}

bool cKeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x8000)
		return true;

	else
		return false;
}





