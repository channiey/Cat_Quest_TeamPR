#include "stdafx.h"
#include "Skill_Player_Fire.h"

#include "Export_Function.h"

#include "Effect_Fire.h"
#include "Effect_Range_Quater.h"


CSkill_Player_Fire::CSkill_Player_Fire(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
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
    CGameObject* p = this;

    m_pGraphicDev;
    int i = 0;

    CSkill::Ready_Object();

    m_fSkillDamage = 50;
    m_fSkiilUsage = 3;

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CSkill_Player_Fire::Update_Object(const _float& fTimeDelta)
{
    _int iExit = CSkill::Update_Object(fTimeDelta);

    if (!m_pSKillEffect->Is_Active())
    {
        __super::End();
        m_bActive = false;
    }


    return iExit;
}

void CSkill_Player_Fire::LateUpdate_Object()
{
    CSkill::LateUpdate_Object();
}

void CSkill_Player_Fire::Render_Object()
{
    CSkill::Render_Object();
}

HRESULT CSkill_Player_Fire::Add_Component()
{

    CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW);
    NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_FireSkill_Range", pRangeEffect), E_FAIL);
    m_pRangeEffect = pRangeEffect;


    CEffect_Fire* pFireEffect = CEffect_Fire::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pFireEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_FireSkill_Effect", pFireEffect), E_FAIL);
    m_pSKillEffect = pFireEffect;

    return S_OK;
}

HRESULT CSkill_Player_Fire::Play()
{
    m_pSKillEffect->Play_Effect(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));
    m_pRangeEffect->Play_Effect(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));
    m_pRangeEffect->Get_Transform()->Set_Scale(_vec3{7.f, 7.f, 7.f});
    m_pRangeEffect->Alphaing(1.f, 255, 128);

    m_bActive = true;

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
