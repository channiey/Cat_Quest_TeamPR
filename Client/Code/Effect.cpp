#include "stdafx.h"
#include "..\Header\Effect.h"

#include "Export_Function.h"

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::EFFECT)
{
}

CEffect::CEffect(const CEffect & rhs)
	: Engine::CGameObject(rhs)
{
}

CEffect::~CEffect()
{
}

HRESULT CEffect::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CEffect::Update_Object(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	//Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CEffect::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	//m_pBufferCom->Render_Buffer();

}

HRESULT CEffect::Add_Component()
{
	return S_OK;
}

CEffect * CEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEffect*	pInstance = new CEffect(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect::Free()
{
	__super::Free();
}
