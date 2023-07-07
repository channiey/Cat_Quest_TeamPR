#include "ManaBarUI.h"
#include "Export_Function.h"

CManaBarUI::CManaBarUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
}

CManaBarUI::CManaBarUI(const CManaBarUI& rhs)
	:CUI(rhs)
{
}

CManaBarUI::~CManaBarUI()
{
}

HRESULT CManaBarUI::Ready_Object()
{
	CGameObject::Ready_Object();


	m_bViewUI = false;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX / 2.f, m_pTransformCom->Get_Scale().y, 10.f });



	return S_OK;
}

_int CManaBarUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	

	return iExit;
}

void CManaBarUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CManaBarUI::Render_Object()
{

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

}

HRESULT CManaBarUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_ManaBar", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CManaBarUI* CManaBarUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CManaBarUI* pInstance = new CManaBarUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("ManaBarUI Create Failed");
		return nullptr;
	}
	return pInstance;
}

void CManaBarUI::Free()
{
	__super::Free();
}
