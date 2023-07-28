#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "stdafx.h"


/*

	��� 2

	�÷��̾� 1, ��ų 1  ��Ÿ 1   

	���ͺ� ��ų 10 MONSTERNAME_SKILLNAME

	ȯ�� ������Ʈ 3

	����Ʈ ������ All

	

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
	map<CHANNEL_ID, _bool> m_mapChannel; // ä���� ���� ��� ���θ� ��ȯ�Ѵ�

private:

	map<TCHAR*, FMOD_SOUND*> m_mapSound; // ���� ���ҽ� ������ ���� ��ü 
	
	FMOD_CHANNEL* m_pChannelArr[(_uint)CHANNEL_ID::TYPEEND];  // FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 

	FMOD_SYSTEM* m_pSystem; // ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 



private:
	virtual void				Free();
};

