#include "stdafx.h"
#include "Skill.h"

#include "Export_Function.h"

#include "SkillEffect.h"

CSkill::CSkill(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: m_pGraphicDev(pGraphicDev)
	, m_pOwnerObject(_pOwnerObject)
{
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();
}

CSkill::~CSkill()
{
}

HRESULT CSkill::Ready_Skill()
{
	FAILED_CHECK_RETURN(Add_SkillEffect(), E_FAIL);

	return S_OK;
}

void CSkill::Update_Skill()
{
	if (!m_bPlay) return;
}

void CSkill::LateUpdate_Skill()
{
	if (!m_bPlay) return;
}



HRESULT CSkill::Add_SkillEffect()
{
	return S_OK;
}

void CSkill::Free()
{
	//for_each(m_vecEffect.begin(), m_vecEffect.end(), CDeleteObj());

	Safe_Release(m_pGraphicDev);
}
