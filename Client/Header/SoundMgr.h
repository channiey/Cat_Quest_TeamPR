#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "stdafx.h"


/*

	* 비어 있는 거 찾아서 주는 방식

	* BGM 0 ~ 2 [3]         // 디폴트 크기 -> 체인지 브금 함수 (볼륨 보간)
	
	* PLAYER 3 ~ 5 [3]      // 디폴트 크기
	
	* EFFECT 6 ~ 10 [5]     // 디폴트 크기
	
	* MONSTER 11 ~ 25 [15]


	

*/
//enum class SOUND_TYPE { BGM, PLAYER, MONSTER, EFFECT, ENVIRONMENT, TYPEEND };




class CSoundMgr : public CBase
{
	DECLARE_SINGLETON(CSoundMgr)

private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void Release(); 

//public: // User
//	void Play_Bgm(TCHAR* pSoundKey);
//	void Play_Sound(TCHAR* pSoundKey, const SOUND_TYPE& _eType);
//
//	void Change_Bgm(TCHAR* pSoundKey);

private: // User
	//const CHANNELID& Get_Channel(const SOUND_TYPE& _eType) {};


public: // private
	void PlaySound(TCHAR* pSoundKey, CHANNEL_ID eID, float fVolume);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	void SetChannelVolume(CHANNEL_ID eID, float fVolume);

private:
	void LoadSoundFile(); 

private: // User
	map<CHANNEL_ID, _bool> m_mapChannel; // 채널의 현재 사용 여부를 반환한다

private:

	map<TCHAR*, FMOD_SOUND*> m_mapSound; // 사운드 리소스 정보를 갖는 객체 
	
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];  // FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 

	FMOD_SYSTEM* m_pSystem; // 사운드 ,채널 객체 및 장치를 관리하는 객체 



private:
	virtual void				Free();
};

