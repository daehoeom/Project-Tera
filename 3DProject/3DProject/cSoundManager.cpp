#include "stdafx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
{
	//사운드 시스템 생성
	System_Create(&_system);

	//채널 수 설정 및 초기화
	_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);


	//채널과 사운드를 동적할당
	//메모리 버퍼 및 사운드 생성
	_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	_channel = new Channel*[TOTAL_SOUND_CHANNEL];

	//초기화 go
	memset(_sound, 0, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	memset(_channel, 0, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

}


cSoundManager::~cSoundManager()
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTAL_SOUND_CHANNEL; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i] != NULL) _sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 닫기
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

//사운드 추가
void cSoundManager::addSound(std::string keyName, std::string soundName, bool background /*= false*/, bool loop /*= false*/)
{
	int a = 0;

	//루프 도니?
	if (loop)
	{
		//배경음악이니?
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	//루프 아님
	else
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//맵에 사운드를 키값과 함께 넣어준다
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

//재생
void cSoundManager::play(std::string keyName, float volume)
{
	m_mapSoundIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			//볼륨 설정
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

//종료
void cSoundManager::stop(std::string keyName)
{
	m_mapSoundIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

//일시 정지
void cSoundManager::pause(std::string keyName)
{
	m_mapSoundIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

//다시 재생
void cSoundManager::resume(std::string keyName)
{
	m_mapSoundIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

//멈춰있니?
bool cSoundManager::isPauseSound(std::string keyName)
{
	bool isPause;
	int count = 0;
	m_mapSoundIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}

//재생중이니?
bool cSoundManager::isPlaySound(std::string keyName)
{
	bool isPlay;
	int count = 0;
	m_mapSoundIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

//fmod update
void cSoundManager::update()
{
	_system->update();

	//볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼내는 등의 다양한 작업을 자동으로 해줌
}