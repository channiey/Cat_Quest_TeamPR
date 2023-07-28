#include "stdafx.h"
#include "SignFish.h"

#include "Export_Function.h"

CSignFish::CSignFish(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_FISH)
{
}

CSignFish::CSignFish(const CSign& rhs)
	: CSign(rhs)
{
}

CSignFish::~CSignFish()
{
}

HRESULT CSignFish::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 367.f, m_pTransformCom->Get_Scale().y, 113.f });

	m_szName = L"SignFish";

	return S_OK;
}

_int CSignFish::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignFish::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignFish::Render_Object()
{
	__super::Render_Object();
}

void CSignFish::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignFish::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignFish::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignFish::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Fish", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignFish* CSignFish::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignFish* pInstance = new CSignFish(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignFish Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignFish::Free()
{
	__super::Free();
}
