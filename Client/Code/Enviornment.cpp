#include "stdafx.h"
#include "..\Header\Enviornment.h"

#include "Export_Function.h"

CEnviornment::CEnviornment(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::ENVIRONMENT)
	, m_pTextureCom(nullptr)
{
}

CEnviornment::CEnviornment(const CEnviornment& rhs)
	: Engine::CGameObject(rhs)
{
}

CEnviornment::~CEnviornment()
{
}

HRESULT CEnviornment::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CEnviornment::Update_Object(const _float& fTimeDelta)
{
	__super::Update_Object(fTimeDelta);

	return 0;
}

void CEnviornment::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEnviornment::Render_Object()
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

HRESULT CEnviornment::Add_Component()
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

void CEnviornment::Free()
{
	__super::Free();
}

//CEnviornment* CEnviornment::Create(LPDIRECT3DDEVICE9 pGraphicDev)
//{
//	CEnviornment* pInstance = new CEnviornment(pGraphicDev);
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
