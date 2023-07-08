#include "UI.h"
#include "Export_Function.h"



CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::UI)
	, m_pTextureCom(nullptr)
	, m_eUIType(UI_TYPE::TYPEEND)

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

	if (m_eUIType == UI_TYPE::VIEW)
	{
		Engine::Add_RenderGroup(RENDER_VIEWUI, this);
	}
	else if (m_eUIType == UI_TYPE::WORLD)
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


void CUI::Free()
{
	__super::Free();
}
