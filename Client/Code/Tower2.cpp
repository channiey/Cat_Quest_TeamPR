#include "stdafx.h"
#include "Tower2.h"

#include "Export_Function.h"

CTower2::CTower2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTower(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_TOWER_2)
{
}

CTower2::CTower2(const CTower& rhs)
	: CTower(rhs)
{
}

CTower2::~CTower2()
{
}

HRESULT CTower2::Ready_Object()
{
	CTower::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 5.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 130.f, m_pTransformCom->Get_Scale().y, 125.f });

	m_szName = L"Tower2";

	return S_OK;
}

_int CTower2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CTower2::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTower2::Render_Object()
{
	__super::Render_Object();
}

void CTower2::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CTower2::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CTower2::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CTower2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Tower2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTower2* CTower2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTower2* pInstance = new CTower2(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Tower2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTower2::Free()
{
	__super::Free();
}
