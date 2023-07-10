#include "LevelUI.h"
#include "Export_Function.h"

CLevelUI::CLevelUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev)
{
}

CLevelUI::CLevelUI(const CLevelUI& rhs)
	: CUI(rhs)
{
}

CLevelUI::~CLevelUI()
{
}

HRESULT CLevelUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;
	
	D3DXMatrixIdentity(&m_UImatWorld);

	m_fPosX = 64;
	m_fPosY = WINCY - 72;

	m_fSizeX =  48;
	m_fSizeY =  64;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CLevelUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CLevelUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CLevelUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
}

HRESULT CLevelUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Level", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CLevelUI* CLevelUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLevelUI* pInstance = new CLevelUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("LevelUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLevelUI::Free()
{
	__super::Free();

}
