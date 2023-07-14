#include "stdafx.h"
#include "..\Header\Item.h"

#include "Export_Function.h"

CItem::CItem(LPDIRECT3DDEVICE9 pGraphicDev , const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::ITEM, _eID)
	, m_pTextureCom(nullptr)
	, m_fJumpingSpeed(0.f)
	, m_eItemType(ITEM_TYPE::TYPEEND)
	, m_vImageSize({ 0.f,0.f,0.f })
{
	ZeroMemory(&m_tStatInfo, sizeof(STATINFO));
}

CItem::CItem(const CItem & rhs)
	: Engine::CGameObject(rhs)
	, m_tStatInfo(rhs.m_tStatInfo)
	, m_fJumpingSpeed(rhs.m_fJumpingSpeed)
	, m_eItemType(rhs.m_eItemType)
	, m_vImageSize(rhs.m_vImageSize)
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
	

	// 각각의 아이템에서 실행 함
	//Engine::Add_RenderGroup(RENDER_ALPHA, this);


	return iExit;
}

void CItem::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CItem::Render_Object()
{
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	//m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetTexture(0, NULL);

	//m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object(); // 콜라이더 출력

}

HRESULT CItem::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Rc Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	// Rc Texture
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

void CItem::Free()
{
	__super::Free();
}
