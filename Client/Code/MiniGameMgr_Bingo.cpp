#include "stdafx.h"
#include "..\Header\MiniGameMgr_Bingo.h"

#include "Export_Function.h"

#include "EventMgr.h"
#include "SoundMgr.h"

#include "FlagOwner.h"
#include "Bingo_Launcher.h"

#include "Bingo_ClearUI.h"
#include "Bingo_FailUI.h"

IMPLEMENT_SINGLETON(CMiniGameMgr_Bingo)

CMiniGameMgr_Bingo::CMiniGameMgr_Bingo()
	: m_bActive(false), m_bInit(false), m_bStart(false), m_bShuffle(false)
	, m_bShowFlag(false)
	, m_iIndex(0), m_iLevel(1), m_iShowIndex(0)
{
}

CMiniGameMgr_Bingo::~CMiniGameMgr_Bingo()
{

}

HRESULT CMiniGameMgr_Bingo::Init(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	m_pGraphicDev = _pGraphicDev;

	// ���� ����
	m_pFlagOwner = CFlagOwner::Create(m_pGraphicDev, OBJ_ID::FLAG_OWNER);
	NULL_CHECK_RETURN(m_pFlagOwner, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(m_pFlagOwner->Get_Name(), m_pFlagOwner), E_FAIL);
	
	// ���� ��ġ
	m_pLauncher = CBingo_Launcher::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pLauncher, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(m_pLauncher->Get_Name(), m_pLauncher), E_FAIL);


	// ����� ����.
	m_FlagVector = m_pFlagOwner->Get_FlagVector();
	// ��� ĭ�� ���� ����.
	m_pStartFlag = dynamic_cast<CFlagStart*>(m_FlagVector.back());

	// ������ ������ ���� ���� ���� ���Ϳ��� ������ ���(��� ĭ) ����.
	m_FlagVector.pop_back();

	m_bInit = true;

	return S_OK;
}

void CMiniGameMgr_Bingo::Update(const _float& _fDelta)
{
	// ��ä�ο� ���� ��
	srand(unsigned int(time(0)));

	// ����ġ ������ �� ���� �ʱ�ȭ.
	if (m_bActive && !m_bStart)
	{
		for (_int i = 0; i < m_FlagVector.size(); ++i)
		{
			m_FlagVector[i]->Ready_Object();
			m_FlagVector[i]->Set_Active(true);
		}
		m_bStart = true;
	}

	// ���� ���� 
	if (m_bActive)
	{
		// �ѹ� ����.
		if (!m_bShuffle)
		{
			// ������ ���� ����ī��Ʈ
			switch (m_iLevel)
			{
			case 1:
				m_iBingoCount = 1;
				break;
			case 2:
				m_iBingoCount = 2;
				break;
			case 3:
				m_iBingoCount = 3;
				break;
			case 4:
				m_iBingoCount = 5;
				break;
			case 5:
				m_iBingoCount = 7;
				break;
			case 6:
				for (_int i = 0; i < m_FlagVector.size(); ++i)
				{
					m_FlagVector[i]->Ready_Object();
					m_FlagVector[i]->Set_Active(false);
				}
				m_bActive = false;
				// m_bStart = true;
				break;
			}

			// ���� ī��Ʈ��ŭ ���
			for (_int i = 0; i < m_iBingoCount; ++i)
			{
				int iRand = rand() % m_FlagVector.size();
				m_BingoVector.push_back(m_FlagVector[iRand]);
			}
			m_bShuffle = true;
			// ������ ������ �ʰ����� ���� ����.
			// if(m_iLevel < 6) m_bShowFlag = true;
			
			m_tFlagShowLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFlagShowLerp.Set_Lerp(1.f, 1.f, 0.f);
		}

		if (m_bShowFlag)
		{
			ShowFlag();
		}
	}
}

void CMiniGameMgr_Bingo::ShowFlag()
{
	if (m_iShowIndex < m_iBingoCount)
	{
		m_tFlagShowLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));

		m_pStartFlag->Set_Texture(
			dynamic_cast<CFlag*>(m_BingoVector[m_iShowIndex])->Get_FlagTag());

		if (!m_tFlagShowLerp.bActive)
		{
			m_pStartFlag->Set_Texture(FLAG_TAG::FLAG_START);
			m_tFlagShowLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFlagShowLerp.Set_Lerp(1.f, 1.f, 0.f);
			m_iShowIndex += 1;

			if (m_iShowIndex < m_iBingoCount)
			{
				CSoundMgr::GetInstance()->PlaySound(L"catnap.wav", CHANNEL_ID::ENVIRONMENT_0, BINGO_SHOW_SOUND);
			}
		}
	}
	else
	{
		m_pStartFlag->Set_Texture(FLAG_TAG::FLAG_START);
		m_bShowFlag = false;
		m_iShowIndex = 0;
	}

}

HRESULT CMiniGameMgr_Bingo::Flag_Check(const OBJ_ID& _eID)
{
	if (m_BingoVector[m_iIndex]->Get_ID() == _eID)
	{
		if (m_iIndex >= m_iBingoCount - 1)
		{
			CSoundMgr::GetInstance()->PlaySound(L"Bingo_AllSucces.mp3", CHANNEL_ID::ENVIRONMENT_0, BINGO_CLEAR_SOUND);
			
			CGameObject* pUI = CBingo_ClearUI::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pUI, E_FAIL);
			CEventMgr::GetInstance()->Add_Obj(L"Bingi_ClearUI", pUI);

			m_iIndex = 0;
			m_iLevel += 1;
			m_BingoVector.clear();
			m_bShuffle = false;

			m_pLauncher->Set_ShowReady(true);
		}
		else
		{
			CSoundMgr::GetInstance()->PlaySound(L"Bingo_Succes.mp3", CHANNEL_ID::ENVIRONMENT_1, BINGO_SUCCES_SOUND);
			m_iIndex += 1;
		}
	}
	else
	{
		CSoundMgr::GetInstance()->PlaySound(L"Bingo_Fail.mp3", CHANNEL_ID::ENVIRONMENT_2, BINGO_FAIL_SOUND);
		CGameObject* pUI = CBingo_FailUI::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pUI, E_FAIL);
		CEventMgr::GetInstance()->Add_Obj(L"Bingo_FailUI", pUI);

		m_pLauncher->Set_ShowReady(true);
		m_iIndex = 0;
	}

	return S_OK;
}

void CMiniGameMgr_Bingo::Free()
{
}
