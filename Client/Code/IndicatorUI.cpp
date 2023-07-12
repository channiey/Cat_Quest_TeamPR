#include "IndicatorUI.h"
#include "Export_Function.h"

CIndicatorUI::CIndicatorUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev), m_pTarget(nullptr)
{
}

CIndicatorUI::CIndicatorUI(const CIndicatorUI& rhs)
	: CUI(rhs)
{
	m_pTarget = rhs.m_pTarget;
}

CIndicatorUI::~CIndicatorUI()
{
}

HRESULT CIndicatorUI::Ready_Object()
{
	CGameObject::Ready_Object();

	m_eUIType = UI_TYPE::WORLD;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.f, 1.f, 1.f });

	return S_OK;
}

_int CIndicatorUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CIndicatorUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CIndicatorUI::Render_Object()
{
	__super::Render_Object();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	
}

HRESULT CIndicatorUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Indicator", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CIndicatorUI* CIndicatorUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIndicatorUI* pInstance = new CIndicatorUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("IndicatorUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CIndicatorUI::Free()
{
	__super::Free();

}
