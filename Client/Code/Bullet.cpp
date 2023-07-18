#include "Bullet.h"

#include "EventMgr.h"
#include "Export_Function.h"


CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    :Engine::CGameObject(pGraphicDev,OBJ_TYPE::BULLET, _eID)
{
}

CBullet::CBullet(const CBullet& rhs)
    :Engine::CGameObject(rhs)
{
}

CBullet::~CBullet()
{
}

HRESULT CBullet::Ready_Object()
{



    return S_OK;
}

_int CBullet::Update_Object(const _float& fTimeDelta)
{



    return _int();
}

void CBullet::LateUpdate_Object()
{
}

void CBullet::Render_Object()
{
}

HRESULT CBullet::Add_Component()
{
    return E_NOTIMPL;
}

CBullet* CBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    return nullptr;
}

void CBullet::Free()
{
}
