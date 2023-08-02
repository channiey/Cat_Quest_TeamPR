#include "Skill_Monster_Fire.h"
#include "EventMgr.h"
#include "Export_Function.h"

#include "Effect_Fire.h"
#include "Effect_Range_Quater.h"

#include "RangeObj.h"
#include "Player.h"

CSkill_Monster_Fire::CSkill_Monster_Fire(LPDIRECT3DDEVICE9 pGraphicDev)
    :CSkill(pGraphicDev, OBJ_ID::SKILL_MONSTER_FIRE)
{
}

CSkill_Monster_Fire::CSkill_Monster_Fire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    :CSkill(pGraphicDev, _pOwnerObject , OBJ_ID::SKILL_MONSTER_FIRE)
{
}

CSkill_Monster_Fire::CSkill_Monster_Fire(const CSkill_Monster_Fire& rhs)
    :CSkill(rhs)
{
}

CSkill_Monster_Fire::~CSkill_Monster_Fire()
{
}

HRESULT CSkill_Monster_Fire::Ready_Object()
{
    __super::Ready_Object();


   
    m_bActive = false;
    m_fSkillDamage = 10;

    m_pBaseRangeEffect = nullptr;

    // Naming
    m_szName = L"Skill_Monster_Fire";


    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CSkill_Monster_Fire::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);
     Engine::Add_RenderGroup(RENDER_ALPHA, this);



    // Dead condition
    if (!m_pOwnerObject->Is_Active())
    {
        End();
        m_pBaseRangeEffect->Set_Active(false);
        CEventMgr::GetInstance()->Delete_Obj(m_pRangeEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect);
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }


    // Pos Setting
    _vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);
    m_pTransformCom->Set_Pos(vPos);
   
                                    
    
    // Skill Play
    if (!m_pSKillEffect->Is_Active())
    {
        End();
        m_bActive = false;
    }


 
    return iExit;
}

void CSkill_Monster_Fire::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CSkill_Monster_Fire::Render_Object()
{
    __super::Render_Object();
}

void CSkill_Monster_Fire::OnCollision_Enter(CGameObject* _pColObj)
{
    switch (_pColObj->Get_Type())
    {
    case Engine::OBJ_TYPE::PLAYER:
    {
        CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
        dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fSkillDamage, this);
    }
    break;
    default:
    {
    }
    break;
    }

}

void CSkill_Monster_Fire::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSkill_Monster_Fire::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSkill_Monster_Fire::Add_Component()
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

    // Effect Range Quater - Base
    m_pBaseRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
    NULL_CHECK_RETURN(m_pBaseRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Fire_Base", m_pBaseRangeEffect), E_FAIL);


    // Ranget Obj
    CRangeObj* pGameObject = CRangeObj::Create(m_pGraphicDev, this, 5.f);
    CSphereCollider* pShpere = dynamic_cast<CSphereCollider*>(pGameObject->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
    pShpere->Set_Radius(10.f);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    CEventMgr::GetInstance()->Add_Obj(L"Monster_Fire_Sphere", pGameObject);
    m_pRangeObj = pGameObject;



    return S_OK;
}

HRESULT CSkill_Monster_Fire::Play()
{
    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    OBJ_ID eObjID = m_pOwnerObject->Get_ID();

    m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
    m_pBaseRangeEffect->Alphaing(0.5f, 240.f, 0.f);
    m_pBaseRangeEffect->Scaling(0.01f, 1.f, 1.f);


    m_bActive = false;

    return S_OK;
}

HRESULT CSkill_Monster_Fire::LatePlay()
{
    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    OBJ_ID eObjID = m_pOwnerObject->Get_ID();


    m_pBaseRangeEffect->Set_Active(false);

    m_pSKillEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
    m_bActive = true;

    m_pRangeObj->Set_Active(true);


    m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
    m_pRangeEffect->Alphaing(1.f, 255, 128);
    m_pRangeEffect->Get_Transform()->Set_Scale(_vec3{ 5.f, 5.f, 5.f });
    m_pRangeEffect->Scaling(1.f, 1.f, 1.f);




    return S_OK;
}

HRESULT CSkill_Monster_Fire::End()
{
   
    m_pSKillEffect->Set_Active(false);
    m_pRangeEffect->Set_Active(false);
    m_bActive = false;

    return S_OK;
}

CSkill_Monster_Fire* CSkill_Monster_Fire::Create(LPDIRECT3DDEVICE9 pGraphicDev , CGameObject* _pOwnerObject)
{
    CSkill_Monster_Fire* pInstance = new CSkill_Monster_Fire(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("CSkill_Monster_Fire Create Failed");
        return nullptr;
    }

    return pInstance;
}


void CSkill_Monster_Fire::Free()
{
    __super::Free();
}
