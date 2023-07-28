#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "stdafx.h"


/*

	* ��� �ִ� �� ã�Ƽ� �ִ� ���

	* BGM 0 ~ 2 [3]         // ����Ʈ ũ�� -> ü���� ��� �Լ� (���� ����)
	
	* PLAYER 3 ~ 5 [3]      // ����Ʈ ũ��
	
	* EFFECT 6 ~ 10 [5]     // ����Ʈ ũ��
	
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
	map<CHANNEL_ID, _bool> m_mapChannel; // ä���� ���� ��� ���θ� ��ȯ�Ѵ�

private:

	map<TCHAR*, FMOD_SOUND*> m_mapSound; // ���� ���ҽ� ������ ���� ��ü 
	
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];  // FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 

	FMOD_SYSTEM* m_pSystem; // ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 



private:
	virtual void				Free();
};

