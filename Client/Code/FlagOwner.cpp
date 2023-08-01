#include "stdafx.h"
#include "FlagOwner.h"
#include "Export_Function.h"

#include "FlagChina.h"
#include "FlagUSA.h"
#include "FlagFrance.h"
#include "FlagGermany.h"
#include "FlagItaly.h"
#include "FlagJapen.h"
#include "FlagRussia.h"
#include "FlagThai.h"
#include "FlagStart.h"

#include "MiniGameMgr_Bingo.h"

CFlagOwner::CFlagOwner(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: CGameObject(pGraphicDev, OBJ_TYPE::FLAG, _eID)
{
	
}

CFlagOwner::CFlagOwner(const CFlagOwner& rhs)
	: CGameObject(rhs)
{
}

CFlagOwner::~CFlagOwner()
{
}

HRESULT CFlagOwner::Ready_Object()
{
	m_vecFlag.push_back(CFlagChina::Create(m_pGraphicDev, this));
	m_vecFlag.push_back(CFlagUSA::Create(m_pGraphicDev, this));
	m_vecFlag.push_back(CFlagFrance::Create(m_pGraphicDev, this));
	m_vecFlag.push_back(CFlagGermany::Create(m_pGraphicDev, this));
	m_vecFlag.push_back(CFlagItaly::Create(m_pGraphicDev, this));
	m_vecFlag.push_back(CFlagJapen::Create(m_pGraphicDev, this));
	m_vecFlag.push_back(CFlagRussia::Create(m_pGraphicDev, this));
	m_vecFlag.push_back(CFlagThai::Create(m_pGraphicDev, this));
	m_vecFlag.push_back(CFlagStart::Create(m_pGraphicDev, this));

	for (_int i = 0; i < m_vecFlag.size(); ++i)
	{
		NULL_CHECK_RETURN(m_vecFlag[i], E_FAIL);
		CEventMgr::GetInstance()->Add_Obj(m_vecFlag[i]->Get_Name(), m_vecFlag[i]);
	}

	m_szName = L"FlagOwner";

	return S_OK;
}

void CFlagOwner::Check_Player_Collision(const OBJ_ID& _eID)
{
	if (OBJ_ID::FLAG_START == _eID)
	{
	}
	else
	{
		if (CInputDev::GetInstance()->Key_Down('E'))
		{
			if (CMiniGameMgr_Bingo::GetInstance()->Get_Active())
				CMiniGameMgr_Bingo::GetInstance()->Flag_Check(_eID);
		}
	}
}

CFlagOwner* CFlagOwner::Create(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
{
	CFlagOwner* pInstance = new CFlagOwner(pGraphicDev, _eID); 

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FlagOwner Create Failed");
		return nullptr;
	}
	return pInstance;
}

void CFlagOwner::Free()
{
}


