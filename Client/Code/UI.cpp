#include "UI.h"
#include "Export_Function.h"



CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::UI)
	, m_pTextureCom(nullptr)
	, m_eUItype(UITYPE_END)
{
}

CUI::CUI(const CUI& rhs)
	:Engine::CGameObject(rhs)
{

}

CUI::~CUI()
{
}

HRESULT CUI::Ready_Object()
{
	CGameObject::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CUI::Update_Object(const _float& fTimeDelta)
{
	__super::Update_Object(fTimeDelta);

	return 0;
}

void CUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CUI::Render_Object()
{


	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();


}

HRESULT CUI::Add_Component()
{
	CComponent* pComponent = nullptr;


	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(COMPONENT_TYPE::TEXTURE, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// RcTex
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CUI* CUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{

	CUI* pInstance = new CUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("UI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CUI::Free()
{
	__super::Free();
}
