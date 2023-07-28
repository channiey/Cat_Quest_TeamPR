#include "SoundMgr.h"
#include "Export_Function.h"

/* ---------------------------- ������ �ݵ�� ���� ���� ---------------------------- */

IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr; 

	m_bPlayingBGM = FALSE;

	ZeroMemory(&m_LerpBgmVolume, sizeof(LERP_FLOAT_INFO));
}


CSoundMgr::~CSoundMgr()
{
	Release(); 
}

void CSoundMgr::Initialize()
{
	FMOD_System_Create(&m_pSystem);
	
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile(); 
}
void CSoundMgr::Update(const _float& fTimeDelta)
{
	if (m_bPlayingBGM && m_LerpBgmVolume.bActive)
	{
		m_LerpBgmVolume.Update_Lerp(fTimeDelta);

		FMOD_Channel_SetVolume(m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR], m_LerpBgmVolume.fCurValue);
	}
}
void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear(); 

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void CSoundMgr::PlaySound(TCHAR * pSoundKey, CHANNEL_ID eID, float fVolume)
{
	StopSound(eID);

	map<TCHAR*, FMOD_SOUND*>::iterator iter; 

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), 
		[&](auto& iter)->bool 
	{
		return !lstrcmp(pSoundKey, iter.first);
	});
	
	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE; 

	if (FMOD_Channel_IsPlaying(m_pChannelArr[(_uint)eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(_uint)eID]);
	}

	FMOD_Channel_SetVolume(m_pChannelArr[(_uint)eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(TCHAR * pSoundKey)
{
	if (!m_bPlayingBGM)
	{
		m_bPlayingBGM = TRUE;
		m_LerpBgmVolume.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
		m_LerpBgmVolume.Set_Lerp(1.f, 0.f, 1.f);
	}

	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
	{
		return !lstrcmp(pSoundKey, iter.first);
	});
	
	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR]);
	FMOD_Channel_SetMode(m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannelArr[(_uint)CHANNEL_ID::BGM_CUR], m_LerpBgmVolume.fCurValue);
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::ChangeBGM(TCHAR* pSoundKey)
{
	if (!m_bPlayingBGM) return;

}

void CSoundMgr::StopSound(CHANNEL_ID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[(_uint)eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0 ; i < (_uint)CHANNEL_ID::TYPEEND; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::SetChannelVolume(CHANNEL_ID eID, float fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[(_uint)eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd; 

	long long handle = _findfirst("../Bin/Resource/Sound/*.*", &fd); // 64bit�ϱ� long lone�̳� intptr_t���� ��� (32bit�� long ��� ����)

	if (handle == -1)
		return; 

	int iResult = 0; 

	char szCurPath[128] = "../Bin/Resource/Sound/";
	char szFullPath[128] = ""; 

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath); 
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr; 
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1; 

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}

		iResult = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);

	_findclose(handle);
}

void CSoundMgr::Free()
{
}