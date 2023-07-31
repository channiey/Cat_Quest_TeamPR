#include "stdafx.h"
#include "..\Header\MiniGameMgr_Bingo.h"

#include "Export_Function.h"

#include "EventMgr.h"
#include "SoundMgr.h"

#include "FlagOwner.h"

IMPLEMENT_SINGLETON(CMiniGameMgr_Bingo)

CMiniGameMgr_Bingo::CMiniGameMgr_Bingo()
	: m_bActive(false)
{
}

CMiniGameMgr_Bingo::~CMiniGameMgr_Bingo()
{

}

HRESULT CMiniGameMgr_Bingo::Init(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	m_pFlagOwner = CFlagOwner::Create(_pGraphicDev, OBJ_ID::FLAG_OWNER);
	NULL_CHECK_RETURN(m_pFlagOwner, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(m_pFlagOwner->Get_Name(), m_pFlagOwner), E_FAIL);
	
	m_FlagVector = m_pFlagOwner->Get_FlagVector();

	m_pGraphicDev = _pGraphicDev;
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
			m_FlagVector[i]->Set_Active(true);
		}
		m_bStart = false;
	}

	// 게임 실행 로직

}

void CMiniGameMgr_Bingo::Free()
{
}
