#include "DefUI.h"
#include "Export_Function.h"

CDefUI::CDefUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev)
{
}

CDefUI::CDefUI(const CDefUI& rhs)
	: CUI(rhs)
{
}

CDefUI::~CDefUI()
{
}

HRESULT CDefUI::Ready_Object()
{
	CGameObject::Ready_Object();


	m_eUIType = UI_TYPE::WORLD;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });

	m_iTranslucent = 100;
	m_bIsReach = false;
	m_fAcc = 0;


	return S_OK;
}

_int CDefUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	m_fAcc += fTimeDelta;

	if (0.01f < m_fAcc)
	{
		if (m_bIsReach)
		{
			m_iTranslucent--;
			if (100 >= m_iTranslucent)
				m_bIsReach = false;
		}
		else if (!m_bIsReach)
		{
			m_iTranslucent++;
			if (225 <= m_iTranslucent)
				m_bIsReach = true;
		}

		m_fAcc = m_fAcc - 0.01f;
	}

	return iExit;
}

void CDefUI::LateUpdate_Object()
{
	Follow_Player();

	__super::LateUpdate_Object();

}

void CDefUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

}

HRESULT CDefUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Ring", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

void CDefUI::Follow_Player()
{
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK(pPlayerTransform);

	_vec3		vPlayerPosition;
	vPlayerPosition = pPlayerTransform->Get_Info(INFO_POS);

	m_pTransformCom->Set_Pos({ vPlayerPosition.x, vPlayerPosition.y, vPlayerPosition.z + 0.1f });
}

CDefUI* CDefUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDefUI* pInstance = new CDefUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("DefUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDefUI::Free()
{
	__super::Free();

}
