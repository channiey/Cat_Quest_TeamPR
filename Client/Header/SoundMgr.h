#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "stdafx.h"


/*

	브금 2

	플레이어 1, 스킬 1  기타 1   

	몬스터별 스킬 10 MONSTERNAME_SKILLNAME

	환경 오브젝트 3

	이펙트 나머지 All

	

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

public:
	void PlaySound(TCHAR* pSoundKey, CHANNEL_ID eID, float fVolume);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	void SetChannelVolume(CHANNEL_ID eID, float fVolume);

private:
	void LoadSoundFile(); 

private: 
	map<CHANNEL_ID, _bool> m_mapChannel; // 채널의 현재 사용 여부를 반환한다

private:

	map<TCHAR*, FMOD_SOUND*> m_mapSound; // 사운드 리소스 정보를 갖는 객체 
	
	FMOD_CHANNEL* m_pChannelArr[(_uint)CHANNEL_ID::TYPEEND];  // FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 

	FMOD_SYSTEM* m_pSystem; // 사운드 ,채널 객체 및 장치를 관리하는 객체 



private:
	virtual void				Free();
};

