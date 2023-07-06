#include "stdafx.h"
#include "..\Header\NPC.h"

#include "Export_Function.h"

CNpc::CNpc(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::NPC)
{
}

CNpc::CNpc(const CNpc & rhs)
	: Engine::CGameObject(rhs)
{
}

CNpc::~CNpc()
{
}

HRESULT CNpc::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CNpc::Update_Object(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	//Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CNpc::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CNpc::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	//m_pBufferCom->Render_Buffer();

}

HRESULT CNpc::Add_Component()
{
	return S_OK;
}

CNpc * CNpc::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNpc*	pInstance = new CNpc(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNpc::Free()
{
	__super::Free();
}
