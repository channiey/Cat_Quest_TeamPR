#include "stdafx.h"
#include "Skill_Player_Thunder.h"

#include "Export_Function.h"

#include "Effect_Thunder.h"
#include "Effect_Range_Quater.h"
#include "SphereCollider.h"
#include "RangeObj.h"
#include "GameObject.h"
#include "Player.h"

CSkill_Player_Thunder::CSkill_Player_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
{
}

CSkill_Player_Thunder::CSkill_Player_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    : CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_PLAYER_THUNDER)
{
}

CSkill_Player_Thunder::CSkill_Player_Thunder(const CSkill_Player_Thunder& rhs)
    : CSkill(rhs)
{
}

CSkill_Player_Thunder::~CSkill_Player_Thunder()
{
}

HRESULT CSkill_Player_Thunder::Ready_Object()
{
    CSkill::Ready_Object();

    m_fSkillDamage = 30;
    m_iSkillUsage = 2;

    m_bActive = false;

   // m_pTransformCom->Set_Scale(_vec3{ 10.f, 10.f, 10.f });

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



    return S_OK;
}

_int CSkill_Player_Thunder::Update_Object(const _float& fTimeDelta)
{
    _int iExit = CSkill::Update_Object(fTimeDelta);

    if (!m_pOwnerObject->Is_Active())
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }
    m_pTransformCom->Set_Pos(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));
 
    
    //m_pRangeObj->Update_Object(fTimeDelta);

    Engine::Add_RenderGroup(RENDER_NONALPHA, this);

    if (!m_pSKillEffect->Is_Active())
    {
        __super::End();
        m_bActive = false;
    }


    return iExit;
}

void CSkill_Player_Thunder::LateUpdate_Object()
{
    //m_pRangeObj->LateUpdate_Object();
    CSkill::LateUpdate_Object();
}

void CSkill_Player_Thunder::Render_Object()
{
   // m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
    //m_pBufferCom->Render_Buffer();
    //m_pRangeObj->Render_Object();
    CSkill::Render_Object();
}

HRESULT CSkill_Player_Thunder::Add_Component()
{

    CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::ARROW_BLUE);
    NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_ThunderSkill_Range", pRangeEffect), E_FAIL);
    m_pRangeEffect = pRangeEffect;
    m_pRangeEffect->Set_Maintain(TRUE); // ������ ���庸��

    CEffect_Thunder* pThunderEffect = CEffect_Thunder::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pThunderEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_ThunderSkill_Effect", pThunderEffect), E_FAIL);
    m_pSKillEffect = pThunderEffect;
    m_pSKillEffect->Set_Maintain(TRUE); // ������ ���庸��

   /* CRangeObj* pGameObject = CRangeObj::Create(m_pGraphicDev, this, 10.f);
    CSphereCollider* pShpere = dynamic_cast<CSphereCollider*>(pGameObject->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
    pShpere->Set_Radius(20.f);
    NULL_CHECK_RETURN(pGameObject, E_FAIL);
    CEventMgr::GetInstance()->Add_Obj(L"Player_ThunderSkill_Sphere", pGameObject);
    m_pRangeObj = pGameObject;*/

   /* CComponent* pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);*/


    return S_OK;
}

HRESULT CSkill_Player_Thunder::Play()
{
    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
   
   
    m_pSKillEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 1 });
    m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4});
    m_pRangeEffect->Alphaing(1.f, 255, 128);
    m_pRangeEffect->Set_Size(_vec3{ 10.f, 5.f, 5.f * 0.7 });
  
    m_bActive = true;

    CCameraMgr::GetInstance()->Shake_Camera(0.15, 30);

    return S_OK;
}

HRESULT CSkill_Player_Thunder::End()
{
    return S_OK;
}

CSkill_Player_Thunder* CSkill_Player_Thunder::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Player_Thunder* pInstance = new CSkill_Player_Thunder(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Player_Thunder Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Player_Thunder::Free()
{
    __super::Free();
}