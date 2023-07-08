#include "stdafx.h"
#include "..\Header\ArgObject.h"

#include "Export_Function.h"

CArgObject::CArgObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::ARGOBJECT)
	, m_pTextureCom(nullptr)
{
}

CArgObject::CArgObject(const CArgObject& rhs)
	: Engine::CGameObject(rhs)
{
}

CArgObject::~CArgObject()
{
}

HRESULT CArgObject::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CArgObject::Update_Object(const _float& fTimeDelta)
{
	__super::Update_Object(fTimeDelta);

	return 0;
}

void CArgObject::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CArgObject::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	if (m_pColliderCom->Is_Collision())
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.green));
	else
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
}

HRESULT CArgObject::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CArgObject::Free()
{
	__super::Free();
}

//CArgObject* CArgObject::Create(LPDIRECT3DDEVICE9 pGraphicDev)
//{
//	CArgObject* pInstance = new CArgObject(pGraphicDev);
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
