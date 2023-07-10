#include "stdafx.h"
#include "Ice_Pillar1.h"

#include "Export_Function.h"

CIce_Pillar1::CIce_Pillar1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CPillar(pGraphicDev)
{
}

CIce_Pillar1::CIce_Pillar1(const CPillar& rhs)
	: CPillar(rhs)
{
}

CIce_Pillar1::~CIce_Pillar1()
{
}

HRESULT CIce_Pillar1::Ready_Object()
{
	CPillar::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 6.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ (VTXCNTX / 2.f) - 70.f, m_pTransformCom->Get_Scale().y - 1.f, -20.f });
	return S_OK;
}

_int CIce_Pillar1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CIce_Pillar1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CIce_Pillar1::Render_Object()
{
	__super::Render_Object();
}

void CIce_Pillar1::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CIce_Pillar1::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CIce_Pillar1::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CIce_Pillar1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Ice_Pillar1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CIce_Pillar1* CIce_Pillar1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIce_Pillar1* pInstance = new CIce_Pillar1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Ice_Pillar1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CIce_Pillar1::Free()
{
	__super::Free();
}
