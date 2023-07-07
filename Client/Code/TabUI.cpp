#include "TabUI.h"
#include "Export_Function.h"

CTabUI::CTabUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
}

CTabUI::CTabUI(const CTabUI& rhs)
	: CUI(rhs)
{
}

CTabUI::~CTabUI()
{
}

HRESULT CTabUI::Ready_Object()
{
	m_bViewUI = true;

	D3DXMatrixIdentity(&matWorld);

	m_fX = 70;
	m_fY = 64;

	m_fSizeX = 62.5f;
	m_fSizeY = 50;

	matWorld._41 = m_fX;
	matWorld._42 = m_fY;

	matWorld._11 = m_fSizeX;
	matWorld._22 = m_fSizeY;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTabUI::Update_Object(const _float& fTimeDelta)
{
	__super::Update_Object(fTimeDelta);

	return 0;
}

void CTabUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTabUI::Render_Object()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CTabUI::Picking_UI()
{
	



}

HRESULT CTabUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Tab", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CTabUI* CTabUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTabUI* pInstance = new CTabUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CTabUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTabUI::Free()
{
	__super::Free();

}
