#include "stdafx.h"
#include "..\Header\Pillar.h"

#include "Export_Function.h"

#include "EventMgr.h"

CPillar::CPillar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEnvironment(pGraphicDev)
{
}

CPillar::CPillar(const CPillar& rhs)
	: CEnvironment(rhs)
{
}

CPillar::~CPillar()
{
}

HRESULT CPillar::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CPillar::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CPillar::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CPillar::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEnvironment::Render_Object();
}

HRESULT CPillar::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Rc Texture
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	// Rect Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	return S_OK;
}

void CPillar::Free()
{
	__super::Free();
}
