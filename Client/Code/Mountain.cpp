#include "stdafx.h"
#include "..\Header\Mountain.h"

#include "Export_Function.h"
#include "EventMgr.h"

CMountain::CMountain(LPDIRECT3DDEVICE9 pGraphicDev)
	:	CEnvironment(pGraphicDev)
{
}

CMountain::CMountain(const CEnvironment& rhs)
	:	CEnvironment(rhs)
{
}

CMountain::~CMountain()
{
}

HRESULT CMountain::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 8.f, 5.f, 8.f });
	m_pTransformCom->Set_Pos(_vec3{ 90.f, m_pTransformCom->Get_Scale().y, 20.f });

	return S_OK;
}

_int CMountain::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CEnvironment::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CMountain::LateUpdate_Object()
{
	CEnvironment::LateUpdate_Object();
}

void CMountain::Render_Object()
{
	CEnvironment::Render_Object();
}

void CMountain::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CMountain::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CMountain::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CMountain::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Mountain", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	return S_OK;
}

CMountain* CMountain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMountain* pInstance = new CMountain(pGraphicDev);

	if (FAILED(pInstance->Ready_Object())) {
		Safe_Release(pInstance);

		MSG_BOX("Mountain Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMountain::Free()
{
	CEnvironment::Free();
}
