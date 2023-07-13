#include "stdafx.h"
#include "..\Header\Item.h"

#include "Export_Function.h"

CItem::CItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::ITEM, OBJ_ID::TYPEEND)
{
}

CItem::CItem(const CItem & rhs)
	: Engine::CGameObject(rhs)
	, m_tStatInfo(rhs.m_tStatInfo)
{
}

CItem::~CItem()
{
}

HRESULT CItem::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CItem::Update_Object(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	//Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CItem::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CItem::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	//m_pBufferCom->Render_Buffer();

}

HRESULT CItem::Add_Component()
{
	return S_OK;
}

CItem * CItem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CItem*	pInstance = new CItem(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Item Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CItem::Free()
{
	__super::Free();
}
