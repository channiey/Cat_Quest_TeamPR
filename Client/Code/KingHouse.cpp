#include "stdafx.h"
#include "KingHouse.h"

#include "Export_Function.h"

CKingHouse::CKingHouse(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHouse(pGraphicDev)
{
}

CKingHouse::CKingHouse(const CHouse& rhs)
	: CHouse(rhs)
{
}

CKingHouse::~CKingHouse()
{
}

HRESULT CKingHouse::Ready_Object()
{
	CHouse::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ (VTXCNTX / 2.f) + 30.f, m_pTransformCom->Get_Scale().y, 40.f });

	return S_OK;
}

_int CKingHouse::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CKingHouse::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CKingHouse::Render_Object()
{
	__super::Render_Object();
}

void CKingHouse::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CKingHouse::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CKingHouse::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CKingHouse::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_KingHouse", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CKingHouse* CKingHouse::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CKingHouse* pInstance = new CKingHouse(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("KingHouse Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CKingHouse::Free()
{
	__super::Free();
}
