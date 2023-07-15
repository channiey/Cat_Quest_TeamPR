#include "stdafx.h"
#include "FireSkill.h"

#include "Export_Function.h"
#include "SkillEffect.h"
#include "Effect_Cast_Yellow.h"
#include "Effect_Fire.h"
#include "Effect_Range_BigCircle.h"

CFireSkill::CFireSkill(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CSkill(pGraphicDev, _pOwnerObject)
{
}

CFireSkill::~CFireSkill()
{
}

HRESULT CFireSkill::Ready_Skill()
{
	__super::Ready_Skill();

	FAILED_CHECK_RETURN(Add_SkillEffect(), E_FAIL);

	return S_OK;
}

void CFireSkill::Update_Skill()
{
	__super::Update_Skill();

}

void CFireSkill::LateUpdate_Skill()
{
	__super::LateUpdate_Skill();
}

HRESULT CFireSkill::Cast()
{
	return S_OK;
}

HRESULT CFireSkill::Add_SkillEffect()
{
	CSkillEffect* pSkillEffect = nullptr;

	// 00. ºö
	pSkillEffect = CEffect_Cast_Yellow::Create(m_pGraphicDev, m_pOwnerObject);
	NULL_CHECK_RETURN(pSkillEffect, E_FAIL);
	
	vector<CSkillEffect*> vecSkill;
	vecSkill.push_back(pSkillEffect);

	m_mapEffect.insert({ PRIORITY_SKILL_LAYER::FIRST, vecSkill });


	
	return S_OK;
}

CFireSkill* CFireSkill::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CFireSkill* pInstance = new CFireSkill(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Skill()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Fire Skill Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFireSkill::Free()
{
	__super::Free();
}
