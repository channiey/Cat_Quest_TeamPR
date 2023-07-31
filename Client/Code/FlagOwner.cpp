#include "stdafx.h"
#include "FlagOwner.h"
#include "Export_Function.h"

#include "FlagChina.h"
#include "FlagUSA.h"
#include "FlagFrance.h"

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
	if (OBJ_ID::FLAG_CHINA == _eID)
	{
		int l = 0;
	}
}

CFlagOwner* CFlagOwner::Create(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
{
	CFlagOwner* pInstance = new CFlagOwner(pGraphicDev, _eID); // 얘를 불러주고 있는데

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


