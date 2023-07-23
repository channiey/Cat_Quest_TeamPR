#include "Mage_Bullet.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Player.h"



CMage_Bullet::CMage_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
    : CBasicProjectile(pGraphicDev, OBJ_ID::PROJECTILE_MAGE_BULLET)
{
    m_pBallOwner = pOwner;
    m_pTarget = pTarget;
    m_vPos = _vPos;
}

CMage_Bullet::CMage_Bullet(const CProjectile& rhs)
    : CBasicProjectile(rhs)
{
}

CMage_Bullet::~CMage_Bullet()
{
}

HRESULT CMage_Bullet::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
    
   // m_vPos += (m_vDir * 5.f);

    m_pTransformCom->Set_Pos(m_vPos);
    m_pTransformCom->Set_Dir(m_pBallOwner->Get_Transform()->Get_Dir());

    m_fDamage = static_cast<CPlayer*>(m_pBallOwner)->Get_StatInfo().fAD;

    m_fSpeed = 20.f;

    m_szName = L"Projectile_MageBullet";

    return S_OK;
}

_int CMage_Bullet::Update_Object(const _float& fTimeDelta)
{
    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

    m_fAccTime += fTimeDelta;

    if (m_fAccTime > 0.5f)
    {
        m_fSpeed -= 0.5f;
        if (m_fSpeed <= 0)
            m_fSpeed = 0;
    }
    if (m_fAccTime >= 1.f || m_fSpeed <= 0)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }

    if (m_pTarget == nullptr)
    {
        m_pTransformCom->Translate(fTimeDelta * m_fSpeed);
        return iExit;
    }
       
    if (!m_pTarget->Is_Active())
    {
        cout << "타겟 사라짐" << endl;
        m_pTarget = nullptr;
    }
       

    if (m_pTarget != nullptr)
    {
        _vec3 vTargetPos = m_pTarget->Get_Transform()->Get_Info(INFO_POS);

        this->m_pAICom->Chase_Target(&vTargetPos, fTimeDelta, m_fSpeed);
    }
    
    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

    return iExit;
}


void CMage_Bullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}


void CMage_Bullet::Render_Object()
{

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);


    __super::Render_Object();
}

void CMage_Bullet::OnCollision_Enter(CGameObject* _pColObj)
{
    __super::OnCollision_Enter(_pColObj);
}

void CMage_Bullet::OnCollision_Stay(CGameObject* _pColObj)
{
    __super::OnCollision_Stay(_pColObj);
}

void CMage_Bullet::OnCollision_Exit(CGameObject* _pColObj)
{
    __super::OnCollision_Exit(_pColObj);
}

HRESULT CMage_Bullet::Add_Component()
{ 
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom  = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_Mage", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}

CMage_Bullet* CMage_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos , CGameObject* pTarget, CGameObject* pOwner)
{
    CMage_Bullet* pInstance = new CMage_Bullet(pGraphicDev,_vPos, pTarget, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("MageBullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CMage_Bullet::Free()
{
    __super::Free();
}
