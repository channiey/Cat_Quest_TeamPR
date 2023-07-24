#include "BlueStar_Bullet.h"
#include "Export_Function.h"

CBlueStar_Bullet::CBlueStar_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
    :CBasicProjectile(pGraphicDev, OBJ_ID::PROJECTILE_STAR_BULLET)
{
    m_vPos = _vPos;
    m_pTarget = pTarget;
    m_pOwner = pOwner;
}

CBlueStar_Bullet::CBlueStar_Bullet(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{
}

CBlueStar_Bullet::~CBlueStar_Bullet()
{

}

HRESULT CBlueStar_Bullet::Ready_Object()
{

    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    
    m_pTransformCom->Set_Pos(m_vPos);
    m_pTransformCom->Set_Dir(_vec3{ 0.f, 0.f, 0.f });


    m_fSpeed = 15.f;

    m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);
    
    m_szName = L"Projectile_Star";

    return S_OK;
 
}

_int CBlueStar_Bullet::Update_Object(const _float& fTimeDelta)
{
    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

    _vec3 vTargetPos = m_pTarget->Get_Transform()->Get_Info(INFO_POS);
    
    _vec3 vDir = - (vTargetPos - m_pTransformCom->Get_Info(INFO_POS));


    _vec3 vOriginDir = m_vOriginPos - m_pTransformCom->Get_Info(INFO_POS);

    _float fDistanceOrigin = D3DXVec3Length(&vOriginDir);


    m_fAccTime += fTimeDelta;

    if (m_fAccTime <= 1.f)
    {
 
        m_fSpeed = 20.f;
        this->m_pAICom->Chase_Target(&vTargetPos, fTimeDelta, m_fSpeed);
       
    }
    else if (m_fAccTime < 2.f)
    {
        m_fSpeed = 5.f;
    }
    else if (m_fAccTime <= 3.f)
    {
        m_fSpeed = 20.f;
        this->m_pAICom->Chase_Target(&m_vOriginPos, fTimeDelta, m_fSpeed);
     
          
   
    }
    else if (m_fAccTime <= 4)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }

    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);


    return iExit;
}

void CBlueStar_Bullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CBlueStar_Bullet::Render_Object()
{
    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);


    __super::Render_Object();
}

HRESULT CBlueStar_Bullet::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_BlueStar", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}

CBlueStar_Bullet* CBlueStar_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
{
    CBlueStar_Bullet* pInstance = new CBlueStar_Bullet(pGraphicDev, _vPos, pTarget, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("BlueStar Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CBlueStar_Bullet::Free()
{
    __super::Free();
}
