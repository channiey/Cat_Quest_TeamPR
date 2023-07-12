#include "stdafx.h"
#include "..\Header\Npc.h"
#include "AIComponent.h"
#include "Export_Function.h"

CNpc::CNpc(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::NPC)
{

}

CNpc::CNpc(const CNpc& rhs)
	: Engine::CGameObject(rhs)
{
	for (size_t i = 0; i < _uint(_uint(STATE_TYPE::TYPEEND)); ++i)
	{
		m_pTextureCom[i] = rhs.m_pTextureCom[i];
	}
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

Engine::_int CNpc::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CNpc::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CNpc::Render_Object()  // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!
{

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));


	__super::Render_Object(); // 콜라이더 출력
}

void CNpc::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNpc::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CNpc::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CNpc::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Rc Tex
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	// Rect Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	// Texture는 각각의 Npc 객체에서 진행 

	return S_OK;
}

void CNpc::Free()
{
	__super::Free();
}

