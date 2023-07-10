#include "RingUI.h"
#include "Export_Function.h"

CRingUI::CRingUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev)
{
}

CRingUI::CRingUI(const CRingUI& rhs)
	: CUI(rhs)
{
}

CRingUI::~CRingUI()
{
}

HRESULT CRingUI::Ready_Object()
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

_int CRingUI::Update_Object(const _float& fTimeDelta)
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

void CRingUI::LateUpdate_Object()
{
	Follow_Player();

	__super::LateUpdate_Object();

}

void CRingUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

}

HRESULT CRingUI::Add_Component()
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

void CRingUI::Follow_Player()
{
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK(pPlayerTransform);

	_vec3		vPlayerPosition;
	vPlayerPosition = pPlayerTransform->Get_Info(INFO_POS);

	m_pTransformCom->Set_Pos({ vPlayerPosition.x, vPlayerPosition.y, vPlayerPosition.z + 0.1f });
}

CRingUI* CRingUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRingUI* pInstance = new CRingUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("RingUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRingUI::Free()
{
	__super::Free();

}
