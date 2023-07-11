#include "stdafx.h"
#include "Bush11.h"

#include "Export_Function.h"

CBush11::CBush11(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev)
{
}

CBush11::CBush11(const CBush& rhs)
	: CBush(rhs)
{
}

CBush11::~CBush11()
{
}

HRESULT CBush11::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ (VTXCNTX / 2.f) - 10.f, m_pTransformCom->Get_Scale().y, -40.f });

	return S_OK;
}

_int CBush11::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush11::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush11::Render_Object()
{
	CBush::Render_Object();
}

void CBush11::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush11::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush11::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush11::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush11", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush11* CBush11::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush11* pInstance = new CBush11(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush11 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush11::Free()
{
	CBush::Free();
}
