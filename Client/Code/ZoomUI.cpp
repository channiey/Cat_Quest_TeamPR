#include "ZoomUI.h"
#include "Export_Function.h"

CZoomUI::CZoomUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev, OBJ_ID::UI_ZOOM)
{
}

CZoomUI::CZoomUI(const CZoomUI& rhs)
	: CUI(rhs)
{
}

CZoomUI::~CZoomUI()
{
}

HRESULT CZoomUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;
	
	D3DXMatrixIdentity(&m_UImatWorld);

	m_iZoomState = 0;

	m_fPosX = WINCX - 75;
	m_fPosY = WINCY - 650;

	m_fSizeX = 52.5;
	m_fSizeY = 56;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CZoomUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	_int dwMouse;
	if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
	{
		if (0 < dwMouse && m_iZoomState == 0)
			m_iZoomState = 1;
		else if(0 > dwMouse && m_iZoomState == 1)
			m_iZoomState = 0;
	}

	return iExit;
}

void CZoomUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CZoomUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	m_pTextureCom->Render_Texture(m_iZoomState);
	m_pBufferCom->Render_Buffer();

	__super::Render_Object();
}

HRESULT CZoomUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Zoom", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CZoomUI* CZoomUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CZoomUI* pInstance = new CZoomUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("ZoomUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CZoomUI::Free()
{
	__super::Free();

}
