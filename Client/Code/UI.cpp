#include "UI.h"
#include "Export_Function.h"



CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::UI)
	, m_pTextureCom(nullptr)
	, m_bViewUI(false)

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

	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_bViewUI)
	{
		Engine::Add_RenderGroup(RENDER_VIEWUI, this);
	}
	else
	{
		Engine::Add_RenderGroup(RENDER_WDUI, this);
	}

	return iExit;
}

void CUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CUI::Render_Object()
{
	


}

HRESULT CUI::Add_Component()
{

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
