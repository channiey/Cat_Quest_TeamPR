#include "WarriorWeapon.h"
#include "Export_Function.h"
#include "EventMgr.h"

CWarriorWeapon::CWarriorWeapon(LPDIRECT3DDEVICE9 pGraphicDev)
    : CItem_Weapon(pGraphicDev, OBJ_ID::ITEM_WARRIOR)
{
}

CWarriorWeapon::CWarriorWeapon(const CItem& rhs)
    : CItem_Weapon(rhs)
{

}

CWarriorWeapon::~CWarriorWeapon()
{
}

HRESULT CWarriorWeapon::Ready_Object()
{
    

    return S_OK;
}

_int CWarriorWeapon::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    return iExit;
}

void CWarriorWeapon::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CWarriorWeapon::Render_Object()
{
    __super::Render_Object();
}

HRESULT CWarriorWeapon::Add_Component()
{
    return S_OK;
}

CWarriorWeapon* CWarriorWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    return nullptr;
}

void CWarriorWeapon::Free()
{
    __super::Free();
}
