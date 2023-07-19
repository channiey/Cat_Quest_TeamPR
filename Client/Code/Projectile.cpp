#include "Projectile.h"

#include "EventMgr.h"
#include "Export_Function.h"


CProjectile::CProjectile(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    :Engine::CGameObject(pGraphicDev,OBJ_TYPE::PROJECTILE, _eID)
{
}

CProjectile::CProjectile(const CProjectile& rhs)
    :Engine::CGameObject(rhs)
{
}

CProjectile::~CProjectile()
{
}

HRESULT CProjectile::Ready_Object()
{
    CGameObject::Ready_Object();

    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



    return S_OK;
}

_int CProjectile::Update_Object(const _float& fTimeDelta)
{
    _int iExit =__super::Update_Object(fTimeDelta);


    return iExit;
}

void CProjectile::LateUpdate_Object()
{

    __super::LateUpdate_Object();
}

void CProjectile::Render_Object()
{

    __super::Render_Object();

}

HRESULT CProjectile::Add_Component()
{
    CComponent* pComponent;

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

   
    return S_OK;
}

void CProjectile::Free()
{
    __super::Free();
}
