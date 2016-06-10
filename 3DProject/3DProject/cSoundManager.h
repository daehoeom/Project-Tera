#pragma once
#include "Singleton.h"
#include "inc\fmod.hpp"

#pragma comment(lib, "lib/fmodex_vc.lib")

#define EXTRA_SOUND_CHANNEL 5
#define SOUNDBUFFER 10

#define TOTAL_SOUND_CHANNEL (EXTRA_SOUND_CHANNEL + SOUNDBUFFER)

#define SOUNDMANAGER cSoundManager::Get()


using namespace FMOD;


class cSoundManager :
	public TSingleton<cSoundManager>
{
public:
	cSoundManager();
	virtual ~cSoundManager();

	//사운드 추가
	void addSound(std::string keyName, std::string soundName, bool background = false, bool loop = false);

	int a = 0;

	//재생
	void play(std::string keyName, float volume);

	//종료
	void stop(std::string keyName);

	//일시 정지
	void pause(std::string keyName);

	//다시 재생
	void resume(std::string keyName);

	//멈춰있니?
	bool isPauseSound(std::string keyName);

	//재생중이니?
	bool isPlaySound(std::string keyName);

	//fmod update
	void update();

private:
	typedef std::map<std::string, Sound**> m_mapSound;
	typedef std::map<std::string, Sound**>::iterator m_mapSoundIter;
	typedef std::map<std::string, Channel**> m_mapChannel;
	typedef std::map<std::string, Channel**>::iterator m_mapChannelter;

private:
	System* _system;
	Sound** _sound;

	Channel** _channel;

	m_mapSound _mTotalSounds;
};

