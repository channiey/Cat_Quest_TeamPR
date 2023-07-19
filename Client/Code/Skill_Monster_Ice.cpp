#include "Skill_Monster_Ice.h"
#include "EventMgr.h"
#include "Export_Function.h"

#include "Effect_Ice.h"
#include "Effect_Range_Quater.h"

CSkill_Monster_Ice::CSkill_Monster_Ice(LPDIRECT3DDEVICE9 pGraphicDev)
    :CSkill(pGraphicDev, OBJ_ID::SKILL_MONSTER_ICE)
{
}

CSkill_Monster_Ice::CSkill_Monster_Ice(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
    :CSkill(pGraphicDev, _pOwnerObject , OBJ_ID::SKILL_MONSTER_ICE)
{
}

CSkill_Monster_Ice::CSkill_Monster_Ice(const CSkill_Monster_Ice& rhs)
    :CSkill(rhs)
{
}

CSkill_Monster_Ice::~CSkill_Monster_Ice()
{
}

HRESULT CSkill_Monster_Ice::Ready_Object()
{

    __super::Ready_Object();

    m_pTransformCom->Set_Scale({ 5.f,5.f,5.f }); // Rect 크기 설정

    m_fSkillDamage = 20;
    

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



    m_szName = L"Skill_Monster_Ice";

    return S_OK;
}

_int CSkill_Monster_Ice::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    // 위치 선정 
    _vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);
    m_pTransformCom->Set_Pos(vPos);


    if (!m_pSKillEffect->Is_Active())
    {
        //__super::End(); // 바닥, 이펙트 둘다일 때만
        m_pSKillEffect->Set_Active(FALSE);
        m_bActive = false;
    }



    return iExit;
}

void CSkill_Monster_Ice::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CSkill_Monster_Ice::Render_Object()
{

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());  // Rect 사용 시
    __super::Render_Object();
}

HRESULT CSkill_Monster_Ice::Add_Component()
{
    // Skill Effect
    CSkillEffect* pIceEffect = CEffect_Ice::Create(m_pGraphicDev, this);
    NULL_CHECK_RETURN(pIceEffect, E_FAIL);
    FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_IceSkill_Effect", pIceEffect), E_FAIL);
    m_pSKillEffect = pIceEffect;

    //// Effect Range Quater
    //CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW);
    //NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
    //FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_FireSkill_Range", pRangeEffect), E_FAIL);
    //m_pRangeEffect = pRangeEffect;

     // Rect Collider 
    CComponent* pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);



    return S_OK;
}

HRESULT CSkill_Monster_Ice::Play()
{

    m_pSKillEffect->Play_Effect({ m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS) });
    ///*m_pRangeEffect->Play_Effect({ m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS) });
    //m_pRangeEffect->Get_Transform()->Set_Scale(_vec3{ 7.f, 7.f, 7.f });
    //m_pRangeEffect->Scaling(1.f,1.f,2.f);*/
  


    m_bActive = true;

    return S_OK;
}

HRESULT CSkill_Monster_Ice::End()
{
    return S_OK;
}

CSkill_Monster_Ice* CSkill_Monster_Ice::Create(LPDIRECT3DDEVICE9 pGraphicDev , CGameObject* _pOwnerObject)
{
    CSkill_Monster_Ice* pInstance = new CSkill_Monster_Ice(pGraphicDev, _pOwnerObject);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("CSkill_Monster_Ice Create Failed");
        return nullptr;
    }

    return pInstance;
}


void CSkill_Monster_Ice::Free()
{
    __super::Free();
}
