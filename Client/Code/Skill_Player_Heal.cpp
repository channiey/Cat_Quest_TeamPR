#include "stdafx.h"
#include "Skill_Player_Heal.h"

#include "Export_Function.h"

#include "SphereCollider.h"
#include "RangeObj.h"
#include "GameObject.h"
#include "Player.h"

CSkill_Player_Heal::CSkill_Player_Heal(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CSkill(pGraphicDev, _eID)
{
}

CSkill_Player_Heal::CSkill_Player_Heal(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    : CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_PLAYER_HEAL)
{
}

CSkill_Player_Heal::CSkill_Player_Heal(const CSkill_Player_Heal& rhs)
    : CSkill(rhs)
{
}

CSkill_Player_Heal::~CSkill_Player_Heal()
{
}

HRESULT CSkill_Player_Heal::Ready_Object()
{
    CSkill::Ready_Object();

    //m_iSkillUsage = 2;
    //m_iLv = 0;

    m_bAttackStart = false;
    m_bActive = false;
    m_bIsEffectEnd = false;

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

  /*  m_fontColor = D3DCOLOR_ARGB(255, 102, 0, 0);
    m_contentStr = L"적을 불태워 많은 피해를 입힐 수 있습니다!";*/


    return S_OK;
}

_int CSkill_Player_Heal::Update_Object(const _float& fTimeDelta)
{
    _int iExit = CSkill::Update_Object(fTimeDelta);

    NULL_CHECK_RETURN(m_pOwnerObject, E_FAIL);

    if (!m_pOwnerObject->Is_Active())
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
        return iExit;
    }
    m_pTransformCom->Set_Pos(m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS));


    //m_pRangeObj->Update_Object(fTimeDelta);

    //Engine::Add_RenderGroup(RENDER_ALPHA, this);

    //if (!m_bAttackStart && m_pSKillEffect->Get_Animator()->Get_CurAniamtion()->Get_CurFrame() == 4)
    //{
    //    //static_cast<CPlayer*>(m_pOwnerObject)->Set_Skill(true);
    //    m_bAttackStart = true;
    //}


   /* if (!m_pSKillEffect->Is_Active() && !m_bIsEffectEnd)
    {
        m_pRangeEffect->Alphaing(0.3f, 127, 0);
        m_bIsEffectEnd = true;
    }
    else if (!m_pRangeEffect->Get_AlphaInfo().bActive && m_bIsEffectEnd)
    {
        m_bIsEffectEnd = false;
        __super::End();
        m_bAttackStart = false;
        m_bActive = false;
    }*/


    return iExit;
}

void CSkill_Player_Heal::LateUpdate_Object()
{
    // 나중에 꼭수정 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    m_bActive = false;


    CSkill::LateUpdate_Object();
}

void CSkill_Player_Heal::Render_Object()
{
    CSkill::Render_Object();
}

HRESULT CSkill_Player_Heal::Add_Component()
{
    return S_OK;
}

HRESULT CSkill_Player_Heal::Play()
{
    NULL_CHECK_RETURN(m_pOwnerObject, E_FAIL);

    _vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);

    _float fHeal = 50.f;
    static_cast<CPlayer*>(m_pOwnerObject)->Regen_HP(fHeal + rand() % 10);

   /* m_pSKillEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 1 });
    m_pRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
    m_pRangeEffect->Alphaing(1.f, 255, 128);
    m_pRangeEffect->Set_Size(_vec3{ 7.5f, 7.5f, 7.5f * 0.7 });
    CCameraMgr::GetInstance()->Shake_Camera(0.15, 30);*/
   
    m_bActive = true;

    return S_OK;
}

HRESULT CSkill_Player_Heal::End()
{
    return S_OK;
}

CSkill_Player_Heal* CSkill_Player_Heal::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
    CSkill_Player_Heal* pInstance = new CSkill_Player_Heal(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Skill_Player_Heal Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CSkill_Player_Heal::Free()
{
    __super::Free();
}
