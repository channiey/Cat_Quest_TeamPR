#include "stdafx.h"
#include "..\Header\Building.h"

#include "Export_Function.h"

#include "EventMgr.h"

CBuilding::CBuilding(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos)
	: CEnvironment(pGraphicDev)
{
}

CBuilding::CBuilding(const CEnvironment& rhs)
	: CEnvironment(rhs)
{

}

CBuilding::~CBuilding()
{
}

HRESULT CBuilding::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX / 2.f, m_pTransformCom->Get_Scale().y, 40.f });

	return S_OK;
}

Engine::_int CBuilding::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CEnvironment::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBuilding::LateUpdate_Object()
{
	CEnvironment::LateUpdate_Object();
}

void CBuilding::Render_Object()
{
	CEnvironment::Render_Object();
}

void CBuilding::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBuilding::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBuilding::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBuilding::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Building", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CBuilding::Free()
{
	CEnvironment::Free();
}

CBuilding* CBuilding::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBuilding* pInstance = new CBuilding(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Building Create Failed");
		return nullptr;
	}

	return pInstance;
}

CBuilding* CBuilding::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos)
{
	return nullptr;
}
