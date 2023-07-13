#include "stdafx.h"
#include "FieldSkillUI.h"
#include "Export_Function.h"

CFieldSkillUI::CFieldSkillUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
	, m_bPick(false)
{
}

CFieldSkillUI::CFieldSkillUI(const CFieldSkillUI& rhs)
	: CUI(rhs)
{
}

CFieldSkillUI::~CFieldSkillUI()
{
}

HRESULT CFieldSkillUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV1;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = false;

	return S_OK;
}

_int CFieldSkillUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	//Picking_UI();

	return iExit;
}

void CFieldSkillUI::LateUpdate_Object()
{
	D3DXMatrixIdentity(&m_UImatWorld);

	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY >> 1;
	m_fSizeX = WINCX;
	m_fSizeY = WINCY;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	//m_rcUI[0] = { long(m_fPosX - m_fSizeX / 2.f) , long(m_fPosY - m_fSizeY / 2.f) , long(m_fPosX + m_fSizeX / 2.f) , long(m_fPosY + m_fSizeY / 2.f) };

	__super::LateUpdate_Object();
}

void CFieldSkillUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
}

void CFieldSkillUI::Picking_UI()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	pt.y = WINCY - pt.y;

	if (PtInRect(&m_rcUI[0], pt))
	{
		m_bPick = true;

	}
	else
	{
		m_bPick = false;
	}

}

HRESULT CFieldSkillUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Shade", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CFieldSkillUI* CFieldSkillUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFieldSkillUI* pInstance = new CFieldSkillUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FieldSkillUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFieldSkillUI::Free()
{
	__super::Free();

}
