#include "FoxFire.h"
#include "Export_Function.h"



CFoxFire::CFoxFire(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CProjectile(pGraphicDev , _eID)
{
}

CFoxFire::CFoxFire(const CProjectile& rhs)
    :CProjectile(rhs)
{
}

CFoxFire::~CFoxFire()
{
}

HRESULT CFoxFire::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



    m_szName = L"FoxFire";

    return S_OK;
}

_int CFoxFire::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    return iExit;
}


void CFoxFire::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}


void CFoxFire::Render_Object()
{
    __super::Render_Object();
}

HRESULT CFoxFire::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(COMPONENT_TYPE::TEXTURE, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);





    return S_OK;
}

CFoxFire* CFoxFire::Create(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
{
    CFoxFire* pInstance = new CFoxFire(pGraphicDev, _eID);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("FoxFire Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CFoxFire::Free()
{
    __super::Free();
}
