#include "stdafx.h"
#include "Rock4.h"

#include "Export_Function.h"

CRock4::CRock4(LPDIRECT3DDEVICE9 pGraphicDev)
	: CRock(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_ROCK_4)
{
}

CRock4::CRock4(const CRock& rhs)
	: CRock(rhs)
{
}

CRock4::~CRock4()
{
}

HRESULT CRock4::Ready_Object()
{
	CRock::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 0.5f, 0.5f, 0.5f });
	m_pTransformCom->Set_Pos(_vec3{ 105.f, m_pTransformCom->Get_Scale().y, 90.f });
	return S_OK;
}

_int CRock4::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CRock4::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CRock4::Render_Object()
{
	__super::Render_Object();
}

HRESULT CRock4::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Rock4", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CRock4* CRock4::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRock4* pInstance = new CRock4(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Rock4 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRock4::Free()
{
	__super::Free();
}
