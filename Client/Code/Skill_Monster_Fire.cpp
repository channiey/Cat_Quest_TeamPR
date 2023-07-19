#include "Skill_Monster_Fire.h"

CSkill_Monster_Fire::CSkill_Monster_Fire(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    :CSkill(pGraphicDev, _eID)
{
}

CSkill_Monster_Fire::CSkill_Monster_Fire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID)
    :CSkill(pGraphicDev,  ,_eID)
{
}

CSkill_Monster_Fire::CSkill_Monster_Fire(const CSkill_Monster_Fire& rhs)
{
}

CSkill_Monster_Fire::~CSkill_Monster_Fire()
{
}

HRESULT CSkill_Monster_Fire::Ready_Object()
{
    return E_NOTIMPL;
}

_int CSkill_Monster_Fire::Update_Object(const _float& fTimeDelta)
{
    return _int();
}

void CSkill_Monster_Fire::LateUpdate_Object()
{
}

void CSkill_Monster_Fire::Render_Object()
{
}

HRESULT CSkill_Monster_Fire::Add_Component()
{
    return E_NOTIMPL;
}

HRESULT CSkill_Monster_Fire::Play()
{
    return E_NOTIMPL;
}

HRESULT CSkill_Monster_Fire::End()
{
    return E_NOTIMPL;
}

CSkill_Monster_Fire* CSkill_Monster_Fire::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    return nullptr;
}

void CSkill_Monster_Fire::Free()
{
}
