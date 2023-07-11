#include "stdafx.h"
#include "Bush1.h"

#include "Export_Function.h"

CBush1::CBush1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev)
{
}

CBush1::CBush1(const CBush& rhs)
	: CBush(rhs)
{
}

CBush1::~CBush1()
{
}

HRESULT CBush1::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.0f, 3.5f, 3.5f });
	m_pTransformCom->Set_Pos(_vec3{ (VTXCNTX / 2.f) - 40.f, m_pTransformCom->Get_Scale().y, -20.f });

	return S_OK;
}

_int CBush1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush1::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush1::Render_Object()
{
	CBush::Render_Object();
}

void CBush1::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush1::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush1::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush1* CBush1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush1* pInstance = new CBush1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush1::Free()
{
	CBush::Free();
}