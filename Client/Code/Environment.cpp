#include "stdafx.h"
#include "..\Header\Environment.h"

#include "Export_Function.h"

CEnvironment::CEnvironment(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::ENVIRONMENT)
	, m_pTextureCom(nullptr)
{
}

CEnvironment::CEnvironment(const CEnvironment& rhs)
	: Engine::CGameObject(rhs)
{
}

CEnvironment::~CEnvironment()
{
}

HRESULT CEnvironment::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CEnvironment::Update_Object(const _float& fTimeDelta)
{
	__super::Update_Object(fTimeDelta);

	return 0;
}

void CEnvironment::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEnvironment::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object(); // 콜라이더 출력

}

HRESULT CEnvironment::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	return S_OK;
}

void CEnvironment::Free()
{
	__super::Free();
}

//CEnvironment* CEnvironment::Create(LPDIRECT3DDEVICE9 pGraphicDev)
//{
//	CEnvironment* pInstance = new CEnvironment(pGraphicDev);
//
//	if (FAILED(pInstance->Ready_Object()))
//	{
//		Safe_Release(pInstance);
//
//		MSG_BOX("Monster Create Failed");
//		return nullptr;
//	}
//
//	return pInstance;
//}
