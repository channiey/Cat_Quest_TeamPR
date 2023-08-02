#include "Dagger.h"
#include "Export_Function.h"
#include "Player.h"
#include "SoundMgr.h"

CDagger::CDagger(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
    :CBasicProjectile(pGraphicDev, OBJ_ID::PROJECTILE_CURVE_BULLET)
{
    m_vPos = _vPos;
    m_pTarget = pTarget;
    m_pOwner = pOwner;

    ZeroMemory(&m_tAlpha, sizeof(LERP_FLOAT_INFO));
}

CDagger::CDagger(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{

}

CDagger::~CDagger()
{

}

HRESULT CDagger::Ready_Object()
{

    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    
    m_pTransformCom->Set_Pos(m_vPos);
    m_fSpeed = 40.f;

    m_bNonTarget = false;

    m_bInit = false;


    m_fDamage = 7.f;

    m_szName = L"Projectile_Dagger";

    return S_OK;
 
}

_int CDagger::Update_Object(const _float& fTimeDelta)
{
    if (false == m_bInit)
    {
      
        m_tAlpha.Init_Lerp();
        m_tAlpha.Set_Lerp(0.5f, 0.f, 255.f);
        m_bInit = true;
    }

    if (m_pOwner->Is_Active() == false)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }

    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);


    m_tAlpha.Update_Lerp(fTimeDelta);

    m_fAccTime += fTimeDelta;

    _vec3 vTargetPos = m_pTarget->Get_Transform()->Get_Info(INFO_POS);


    _vec3 vBulletDir = vTargetPos - m_vPos;


    if (m_fAccTime <= 3.f)
    {
        m_pTransformCom->Set_Dir(vec3.zero);

    }
    if (m_fAccTime > 3.f && m_bNonTarget == false)
    {
        m_pTransformCom->Set_Dir(vBulletDir);
        //this->m_pAICom->Chase_TargetY(&vTargetPos, fTimeDelta, m_fSpeed);
        //vBulletDir = m_pTransformCom->Get_Dir();
        m_bNonTarget = true;
    }
    if (m_fAccTime >= 4.f)
    {
        // m_pTransformCom->Set_Dir(vBulletDir);
       // m_fSpeed = 40.f;
    }

    if (m_fAccTime >= 5.f)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }

    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

    return iExit;
}

void CDagger::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CDagger::Render_Object()
{
    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_tAlpha.fCurValue), 255, 255, 255));

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);

    m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB( 255, 255, 255, 255));

    __super::Render_Object();
}

void CDagger::OnCollision_Enter(CGameObject* _pColObj)
{
    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));


    switch (_pColObj->Get_Type())
    {
    case OBJ_TYPE::PLAYER:

        dynamic_cast<CPlayer*>(pPlayer)->Damaged(m_fDamage, this);
        CEventMgr::GetInstance()->Delete_Obj(this);
        break;
    default:
        break;
    }


}

void CDagger::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDagger::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDagger::Add_Component()
{ 
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_GreenDager", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}

CDagger* CDagger::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
{
    CDagger* pInstance = new CDagger(pGraphicDev, _vPos, pTarget, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Dagger Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CDagger::Free()
{
    __super::Free();
}
