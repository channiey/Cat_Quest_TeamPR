#include "stdafx.h"
#include "..\Header\Effect.h"

#include "Export_Function.h"

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::EFFECT)
{
}

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::EFFECT)
	, m_pOwnerobject(_pOwnerObject)
{
	ZeroMemory(&m_vOffSet, sizeof(_vec3));
	ZeroMemory(&m_vSize, sizeof(_vec3));

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

	m_bActive = false;

	return S_OK;
}

_int CEffect::Update_Object(const _float & fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	//m_pAnimatorCom->Update_Animator(fTimeDelta);

	return iExit;
}

void CEffect::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect::Render_Object()
{
	//m_pAnimatorCom->Render_Animator();

	__super::Render_Object(); // 콜라이더 출력
}


HRESULT CEffect::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

	return S_OK;
}

CEffect * CEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect*	pInstance = new CEffect(pGraphicDev, _pOwnerObject);

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
