#include "QuestUI.h"
#include "Export_Function.h"

#include "QuestMgr.h"

CQuestUI::CQuestUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_QUEST)
{
}

CQuestUI::CQuestUI(const CQuestUI& rhs)
	: CUI(rhs)
	, m_pQuestUITexCom(rhs.m_pQuestUITexCom)
	, m_matQuestUI(rhs.m_matQuestUI)
	, m_QuestTitleRc(rhs.m_QuestTitleRc)
	, m_QuestContentRc(rhs.m_QuestContentRc)
{
}

CQuestUI::~CQuestUI()
{
}

HRESULT CQuestUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DXMatrixIdentity(&m_matQuestUI);

	// 퀘스트 UI
	m_fPosX = WINCX - 100;
	m_fPosY = WINCY - 200;
	m_fSizeX = 100.f;
	m_fSizeY = 150.f;
	m_matQuestUI._41 = m_fPosX;
	m_matQuestUI._42 = m_fPosY;
	m_matQuestUI._11 = m_fSizeX;
	m_matQuestUI._22 = m_fSizeY;

	// 제목
	m_QuestTitleRc = { WINCX - 300, WINCY - 670, WINCX - 300, WINCY - 670 };
	// 내용

	return S_OK;
}

_int CQuestUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CQuestUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CQuestUI::Render_Object()
{
	// m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	// m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matQuestUI);

	// m_pQuestUITexCom->Render_Texture();

	// m_pBufferCom->Render_Buffer();

	// 보고 싶을 때만
	if (CQuestMgr::GetInstance()->Get_Quest()->Get_ShowQuestView())
	{
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, CQuestMgr::GetInstance()->Get_Quest()->Get_QuestName().c_str(), -1,
			&m_QuestTitleRc, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

		for (_int i = 0; i < CQuestMgr::GetInstance()->Get_Quest()->Get_QuestContent().size(); ++i)
		{
			m_QuestContentRc = { WINCX - 300, WINCY - 620 + (i * 50), WINCX - 300, WINCY - 620 + (i * 50) };

			if (!CQuestMgr::GetInstance()->Get_Quest()->Get_QuestContent()[i].m_bClear)
			{
				CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, CQuestMgr::GetInstance()->Get_Quest()->Get_QuestContent()[i].m_strQuestContent.c_str(), -1,
					&m_QuestContentRc, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, CQuestMgr::GetInstance()->Get_Quest()->Get_QuestContent()[i].m_strQuestContent.c_str(), -1,
					&m_QuestContentRc, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 204, 0));
			}
		}
	}



	__super::Render_Object();
}

HRESULT CQuestUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pQuestUITexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Quest", this));
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
