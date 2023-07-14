#include "Item_Weapon.h"

CItem_Weapon::CItem_Weapon(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    :CItem(pGraphicDev, _eID)
{
}

CItem_Weapon::CItem_Weapon(const CItem& rhs)
    :CItem(rhs)
{
}

CItem_Weapon::~CItem_Weapon()
{
}

HRESULT CItem_Weapon::Ready_Object()
{

    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_eItemType = ITEM_TYPE::WEAPON;

    return S_OK;
}

_int CItem_Weapon::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    return iExit;
}

void CItem_Weapon::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CItem_Weapon::Render_Object()
{
    __super::Render_Object();
}

HRESULT CItem_Weapon::Add_Component()
{
    return S_OK;
}

void CItem_Weapon::Free()
{
    __super::Free();
}
