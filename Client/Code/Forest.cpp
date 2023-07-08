#include "stdafx.h"
#include "..\Header\Forest.h"

#include "Export_Function.h"

#include "EventMgr.h"

CForest::CForest(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEnvironment(pGraphicDev)
{
}

CForest::CForest(const CEnvironment& rhs)
	: CEnvironment(rhs)
{
}

CForest::~CForest()
{
}

HRESULT CForest::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 30.f, m_pTransformCom->Get_Scale().y, 20.f });

	return S_OK;
}

_int CForest::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CEnvironment::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CForest::LateUpdate_Object()
{
	CEnvironment::LateUpdate_Object();
}

void CForest::Render_Object()
{
	CEnvironment::Render_Object();
}

void CForest::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CForest::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CForest::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CForest::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Forest", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CForest* CForest::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CForest* pInstance = new CForest(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Forest Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CForest::Free()
{
	CEnvironment::Free();
}
