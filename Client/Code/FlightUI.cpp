#include "FlightUI.h"
#include "Export_Function.h"

#include "Player.h"

CFlightUI::CFlightUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev, OBJ_ID::UI_FLIGHT), m_pPlayer(nullptr)
{
}

CFlightUI::CFlightUI(const CFlightUI& rhs)
	: CUI(rhs)
{
	m_pPlayer = rhs.m_pPlayer;
}

CFlightUI::~CFlightUI()
{
}

HRESULT CFlightUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;
	
	D3DXMatrixIdentity(&m_UImatWorld);

	m_fPosX = 100;
	m_fPosY = 160;

	m_fSizeX = 46.8;
	m_fSizeY = 56.7;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = WINCY - m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = false;

	return S_OK;
}

_int CFlightUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (nullptr == m_pPlayer)
		m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
		
	return iExit;
}

void CFlightUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CFlightUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	__super::Render_Object();
}

HRESULT CFlightUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Flight", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CFlightUI* CFlightUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFlightUI* pInstance = new CFlightUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FlightUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFlightUI::Free()
{
	__super::Free();

}
