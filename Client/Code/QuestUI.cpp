#include "QuestUI.h"
#include "Export_Function.h"

CQuestUI::CQuestUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_QUEST)
{
}

CQuestUI::CQuestUI(const CQuestUI& rhs)
	: CUI(rhs)
{
}

CQuestUI::~CQuestUI()
{
}

HRESULT CQuestUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;

	D3DXMatrixIdentity(&m_UImatWorld);

	m_iZoomState = 0;

	m_fPosX = WINCX - 100;
	m_fPosY = WINCY - 200;

	m_fSizeX = 100.f;
	m_fSizeY = 150.f;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CQuestUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	_int dwMouse;
	if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
	{
		if (0 < dwMouse && m_iZoomState == 0)
			m_iZoomState = 1;
		else if (0 > dwMouse && m_iZoomState == 1)
			m_iZoomState = 0;
	}

	return iExit;
}

void CQuestUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CQuestUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	m_pTextureCom->Render_Texture(m_iZoomState);
	m_pBufferCom->Render_Buffer();

	__super::Render_Object();
}

HRESULT CQuestUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Quest", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CQuestUI* CQuestUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CQuestUI* pInstance = new CQuestUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("QuestUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CQuestUI::Free()
{
	__super::Free();

}
