#include "Skill_Monster_Beam.h"
#include "EventMgr.h"
#include "Export_Function.h"

#include "Effect_Beam.h"
#include "Effect_Range_Quater.h"
#include "RangeObj.h"
#include "Monster.h"

CSkill_Monster_Beam::CSkill_Monster_Beam(LPDIRECT3DDEVICE9 pGraphicDev)
    :CSkill(pGraphicDev, OBJ_ID::SKILL_MONSTER_BEAM)
{
}

CSkill_Monster_Beam::CSkill_Monster_Beam(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    :CSkill(pGraphicDev, _pOwnerObject , OBJ_ID::SKILL_MONSTER_BEAM)
  
{
    m_pOwnerObject = _pOwnerObject;
}

CSkill_Monster_Beam::CSkill_Monster_Beam(const CSkill_Monster_Beam& rhs)
    :CSkill(rhs)
{
}

CSkill_Monster_Beam::~CSkill_Monster_Beam()
{
}

HRESULT CSkill_Monster_Beam::Ready_Object()
{
    __super::Ready_Object();

  

    m_bActive = false;
    m_fSkillDamage = 20;
    m_pBaseRangeEffect = nullptr;

    // Naming
    m_szName = L"Skill_Monster_Beam";


    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
    return S_OK;
}

_int CSkill_Monster_Beam::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);
    Engine::Add_RenderGroup(RENDER_ALPHA, this);

    // Dead Condition
    if (dynamic_cast<CMonster*>(m_pOwnerObject)->Is_Dead() == true)
    {
        m_pBaseRangeEffect->Set_Active(false);
        End();
        CEventMgr::GetInstance()->Delete_Obj(m_pRangeEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect);
        CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect);
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

void CSkill_Monster_Beam::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CSkill_Monster_Beam::Render_Object()
{
    __super::Render_Object();
}

HRESULT CSkill_Monster_Beam::Add_Component()
{
    // Skill Effect
    CSkillEffect* pBeamEffect = CEffect_Beam::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pBeamEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_BeamSkill_Effect", pBeamEffect), E_FAIL);
    m_pSKillEffect = pBeamEffect;

    // Effect Range Quater
    CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::SQUARE_PURPLE);
    NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_BeamSkill_Range", pRangeEffect), E_FAIL);
    m_pRangeEffect = pRangeEffect;


    //Effet Range Quater - Base
    m_pBaseRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::SQUARE_RED);
    NULL_CHECK_RETURN(m_pBaseRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Beam_Base", m_pBaseRangeEffect), E_FAIL);


    return S_OK;
}

HRESULT CSkill_Monster_Beam::Play()
{

    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    OBJ_ID eObjID = m_pOwnerObject->Get_ID();

    m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z +4});
    m_pBaseRangeEffect->Alphaing(1.f, 180.f, 180.f);
    m_pBaseRangeEffect->Scaling(0.01f, 0.8f, 0.8f);

    m_bActive = true;

    return S_OK;
}

HRESULT CSkill_Monster_Beam::LatePlay()
{
    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
    OBJ_ID eObjID = m_pOwnerObject->Get_ID();


    m_pBaseRangeEffect->Set_Active(false);

    m_pSKillEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z });
    m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z +4});
    m_pRangeEffect->Alphaing(1.f, 255, 128);
    m_pRangeEffect->Scaling(0.5f, 0.1f, 0.8f);


    return S_OK;
}

HRESULT CSkill_Monster_Beam::End()
{
    
    m_pSKillEffect->Set_Active(false);
    m_pRangeEffect->Set_Active(false);
    return S_OK;
}

CSkill_Monster_Beam* CSkill_Monster_Beam::Create(LPDIRECT3DDEVICE9 pGraphicDev , CGameObject* _pOwnerObject)
{
    CSkill_Monster_Beam* pInstance = new CSkill_Monster_Beam(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("CSkill_Monster_Beam Create Failed");
        return nullptr;
    }

    return pInstance;
}


void CSkill_Monster_Beam::Free()
{
    __super::Free();
}
