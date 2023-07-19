#include "Skill_Player_Fire.h"

#include "Effect_Fire.h"
#include "Effect_Range_Quater.h"

#include "EventMgr.h"


CSkill_Player_Fire::CSkill_Player_Fire(LPDIRECT3DDEVICE9 pGraphicDev)
    : CSkill(pGraphicDev, OBJ_ID::SKILL_PLAYER_FIRE)
{
}

CSkill_Player_Fire::CSkill_Player_Fire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    : CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_PLAYER_FIRE)
{
}

CSkill_Player_Fire::CSkill_Player_Fire(const CSkill_Player_Fire& rhs)
    : CSkill(rhs)
{
}

CSkill_Player_Fire::~CSkill_Player_Fire()
{
}

HRESULT CSkill_Player_Fire::Ready_Object()
{
    CSkill::Ready_Object();

    m_fSkillDamage = 50;
    m_fSkiilUsage = 3;

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CSkill_Player_Fire::Update_Object(const _float& fTimeDelta)
{
    _int iExit = CSkill::Update_Object(fTimeDelta);




    return iExit;
}

void CSkill_Player_Fire::LateUpdate_Object()
{
  
}

void CSkill_Player_Fire::Render_Object()
{
    CSkill::Render_Object();
}

HRESULT CSkill_Player_Fire::Add_Component()
{
    CSkillEffect* pFireEffect = CEffect_Fire::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pFireEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_FireSkill_Effect", pFireEffect), E_FAIL);
    m_pSKillEffect = pFireEffect;

    CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW);
    NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_FireSkill_Range", pRangeEffect), E_FAIL);
    m_pRangeEffect = pRangeEffect;

    return S_OK;
}

HRESULT CSkill_Player_Fire::Play()
{
    return S_OK;
}

HRESULT CSkill_Player_Fire::End()
{
    return S_OK;
}

CSkill_Player_Fire* CSkill_Player_Fire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Player_Fire* pInstance = new CSkill_Player_Fire(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Player_Fire Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Player_Fire::Free()
{
    __super::Free();
}
