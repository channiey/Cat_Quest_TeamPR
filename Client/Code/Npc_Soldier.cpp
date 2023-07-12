#include "stdafx.h"
#include "Npc_Soldier.h"

#include "Export_Function.h"

CNpc_Soldier::CNpc_Soldier(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev)
{
}

CNpc_Soldier::CNpc_Soldier(const CNpc& rhs)
	: CNpc(rhs)
{
}


CNpc_Soldier::~CNpc_Soldier()
{
}

HRESULT CNpc_Soldier::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ (VTXCNTX / 2.f) - 5.f, m_pTransformCom->Get_Scale().y + 3.f, 20.f });
	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });

	return S_OK;
}

_int CNpc_Soldier::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CNpc::Update_Object(fTimeDelta);

	return iExit;
}

void CNpc_Soldier::LateUpdate_Object()
{
	CNpc::LateUpdate_Object();
}

void CNpc_Soldier::Render_Object()
{
	CNpc::Render_Object();
}

void CNpc_Soldier::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNpc_Soldier::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CNpc_Soldier::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CNpc_Soldier::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Npc_Soldier", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CNpc_Soldier* CNpc_Soldier::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNpc_Soldier* pInstance = new CNpc_Soldier(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_Soldier Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNpc_Soldier::Free()
{
	CNpc::Free();
}