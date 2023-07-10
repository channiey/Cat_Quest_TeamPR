#include "HpUI.h"
#include "Export_Function.h"

CHpUI::CHpUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev)
{
}

CHpUI::CHpUI(const CHpUI& rhs)
	: CUI(rhs)
{
}

CHpUI::~CHpUI()
{
}

HRESULT CHpUI::Ready_Object()
{
	CGameObject::Ready_Object();


	m_eUIType = UI_TYPE::WORLD;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });

	return S_OK;
}

_int CHpUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);


	return iExit;
}

void CHpUI::LateUpdate_Object()
{
	Follow_Player();

	__super::LateUpdate_Object();

}

void CHpUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

}

HRESULT CHpUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Bar", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	for (_uint i = 0; i < 4; ++i)
	{
		pComponent = m_pUIBufferCom[i] = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);
	}

	


	return S_OK;
}

void CHpUI::Follow_Player()
{
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK(pPlayerTransform);

	_vec3		vPlayerPosition;
	vPlayerPosition = pPlayerTransform->Get_Info(INFO_POS);

	m_pTransformCom->Set_Pos({ vPlayerPosition.x, vPlayerPosition.y, vPlayerPosition.z + 0.1f });
}

CHpUI* CHpUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHpUI* pInstance = new CHpUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("HpUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHpUI::Free()
{
	__super::Free();

}
