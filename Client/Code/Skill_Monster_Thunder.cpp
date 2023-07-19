#include "Skill_Monster_Thunder.h"
#include "Effect_Fire.h"
#include "Effect_Range_Quater.h"
#include "EventMgr.h"
#include "Export_Function.h"

CSkill_Monster_Thunder::CSkill_Monster_Thunder(LPDIRECT3DDEVICE9 pGraphicDev)
    :CSkill(pGraphicDev, OBJ_ID::SKILL_MONSTER_FIRE)
{
}

CSkill_Monster_Thunder::CSkill_Monster_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    :CSkill(pGraphicDev, _pOwnerObject , OBJ_ID::SKILL_MONSTER_FIRE)
{
}

CSkill_Monster_Thunder::CSkill_Monster_Thunder(const CSkill_Monster_Thunder& rhs)
    :CSkill(rhs)
{
}

CSkill_Monster_Thunder::~CSkill_Monster_Thunder()
{
}

HRESULT CSkill_Monster_Thunder::Ready_Object()
{

    __super::Ready_Object();

    m_fSkillDamage = 20;
    

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



    m_szName = L"Skill_Monster_Fire";

    return S_OK;
}

_int CSkill_Monster_Thunder::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    
    if (!m_pSKillEffect->Is_Active())
    {
        __super::End();
        m_bActive = false;
    }


    return iExit;
}

void CSkill_Monster_Thunder::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CSkill_Monster_Thunder::Render_Object()
{
    __super::Render_Object();
}

HRESULT CSkill_Monster_Thunder::Add_Component()
{
    // Skill Effect
    CSkillEffect* pFireEffect = CEffect_Fire::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pFireEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_FireSkill_Effect", pFireEffect), E_FAIL);
    m_pSKillEffect = pFireEffect;

    // Effect Range Quater
    CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW);
    NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_FireSkill_Range", pRangeEffect), E_FAIL);
    m_pRangeEffect = pRangeEffect;


    return S_OK;
}

HRESULT CSkill_Monster_Thunder::Play()
{

    m_pSKillEffect->Play_Effect({ m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS) });
    m_pRangeEffect->Play_Effect({ m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS) });
    m_pRangeEffect->Get_Transform()->Set_Scale(_vec3{ 7.f, 7.f, 7.f });
    m_pRangeEffect->Scaling(1.f,1.f,2.f);
  


    m_bActive = true;

    return S_OK;
}

HRESULT CSkill_Monster_Thunder::End()
{
    return S_OK;
}

CSkill_Monster_Thunder* CSkill_Monster_Thunder::Create(LPDIRECT3DDEVICE9 pGraphicDev , CGameObject* _pOwnerObject)
{
    CSkill_Monster_Thunder* pInstance = new CSkill_Monster_Thunder(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("CSkill_Monster_Thunder Create Failed");
        return nullptr;
    }

    return pInstance;
}


void CSkill_Monster_Thunder::Free()
{
    __super::Free();
}
