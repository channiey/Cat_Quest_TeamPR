#include "stdafx.h"
#include "Npc_King.h"

#include "Export_Function.h"

CNpc_King::CNpc_King(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev)
{
}

CNpc_King::CNpc_King(const CNpc_King& rhs)
	: CNpc(rhs)
{
}

CNpc_King::~CNpc_King()
{
}

HRESULT CNpc_King::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ (VTXCNTX / 2.f) - 40.f, m_pTransformCom->Get_Scale().y, -20.f });

	return S_OK;
}

_int CNpc_King::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CNpc_King::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CNpc_King::LateUpdate_Object()
{
	CNpc_King::LateUpdate_Object();
}

void CNpc_King::Render_Object()
{
	CNpc_King::Render_Object();
}

void CNpc_King::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNpc_King::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CNpc_King::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CNpc_King::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fRoll", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CNpc_King* CNpc_King::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNpc_King* pInstance = new CNpc_King(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_King Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNpc_King::Free()
{
	CNpc_King::Free();
}
