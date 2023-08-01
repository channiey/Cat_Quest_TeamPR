#include "stdafx.h"
#include "..\Header\MiniGameMgr_Bingo.h"

#include "Export_Function.h"

#include "EventMgr.h"
#include "SoundMgr.h"

#include "FlagOwner.h"

IMPLEMENT_SINGLETON(CMiniGameMgr_Bingo)

CMiniGameMgr_Bingo::CMiniGameMgr_Bingo()
	: m_bActive(false), m_bInit(false), m_bStart(false), m_bShuffle(false)
	, m_iIndex(0), m_iLevel(1)
{
}

CMiniGameMgr_Bingo::~CMiniGameMgr_Bingo()
{

}

HRESULT CMiniGameMgr_Bingo::Init(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	m_pGraphicDev = _pGraphicDev;

	m_pFlagOwner = CFlagOwner::Create(m_pGraphicDev, OBJ_ID::FLAG_OWNER);
	NULL_CHECK_RETURN(m_pFlagOwner, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(m_pFlagOwner->Get_Name(), m_pFlagOwner), E_FAIL);
	
	m_FlagVector = m_pFlagOwner->Get_FlagVector();

	m_bInit = true;

	return S_OK;
}

void CMiniGameMgr_Bingo::Update(const _float& _fDelta)
{
	// 스위치 켜지면 한 번만 초기화.
	if (!m_bActive && m_bStart)
	{
		for (_int i = 0; i < m_FlagVector.size() - 1; ++i)
		{
			m_FlagVector[i]->Ready_Object();
			m_FlagVector[i]->Set_Active(true);
		}
		m_bStart = false;
	}

	// 게임 실행 
	if (m_bStart)
	{
		// 한번 삽입.
		if (!m_bShuffle)
		{
			for (_int i = 0; i < m_iLevel; ++i)
			{
				int iRand = rand() % m_FlagVector.size();
				m_BingoVector.push_back(m_FlagVector[iRand]);
			}
			m_bShuffle = true;
		}
	}
}

void CMiniGameMgr_Bingo::Flag_Check(const OBJ_ID& _eID)
{
	if (m_BingoVector[m_iIndex]->Get_ID() == _eID)
	{
		// 여기서 이어서 
	}
}

void CMiniGameMgr_Bingo::Free()
{
}
