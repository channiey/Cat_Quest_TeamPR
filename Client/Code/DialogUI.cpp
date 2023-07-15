#include "DialogUI.h"
#include "Export_Function.h"

#include "Player.h"

CDialogUI::CDialogUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev, OBJ_ID::UI_DIALOG)
{
}

CDialogUI::CDialogUI(const CDialogUI& rhs)
	: CUI(rhs)
{
}

CDialogUI::~CDialogUI()
{
}

HRESULT CDialogUI::Ready_Object()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eUIType = UI_TYPE::VIEW;
	
	m_fAcc = 0.f;
	m_iTextCnt = 0.f;

	D3DXMatrixIdentity(&m_UImatWorld);
	for (_uint i = 0; i < 2; ++i)
	{
		D3DXMatrixIdentity(&m_matUI[i]);
	}

	m_fPosX = WINCX * 0.5;
	m_fPosY = WINCY * 0.25;

	m_fSizeX =  400;
	m_fSizeY =  124;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;
	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	m_rcText = { long(m_fPosX - (m_fSizeX / 2.f) - 80) , long(WINCY - m_fPosY - m_fSizeY / 2.f) ,
		long(m_fPosX + (m_fSizeX / 2.f) + 100) , long(WINCY - m_fPosY + m_fSizeY / 2.f) };


	return S_OK;
}

_int CDialogUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Typing_Effect(fTimeDelta);

	return iExit;
}

void CDialogUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CDialogUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_strTyping.c_str(), -1,
		&m_rcText, DT_LEFT | DT_WORDBREAK, D3DCOLOR_ARGB(200, 0, 0, 0));

	__super::Render_Object();
}

HRESULT CDialogUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_SpeechBox", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[0] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_ScrollArrow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[1] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_NpcStand", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[2] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_SpiritStand", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

HRESULT CDialogUI::Ready_Dialog(OBJ_ID eNpc, wstring strDialog, SPIRITEMO_TYPE eEmo)
{
	if (0 >= strDialog.size())
		return E_FAIL;

	m_strDialog = strDialog;
	Select_Npc(eNpc, eEmo);

	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_strDialog.c_str(), -1,
		&m_rcText, DT_LEFT | DT_CALCRECT | DT_WORDBREAK, D3DCOLOR_ARGB(200, 0, 0, 0));

	m_UImatWorld._22 = m_rcText.bottom - m_rcText.top + 30;

	return S_OK;
}

void CDialogUI::Select_Npc(OBJ_ID eNpc, SPIRITEMO_TYPE eEmo)
{
	switch (eNpc)
	{
	case OBJ_ID::NPC_BLACKSMITH:
		m_iNpc = 0;
		m_eObjID = OBJ_ID::NPC_BLACKSMITH;
	case OBJ_ID::NPC_CITIZEN_1:
		m_iNpc = 1;
		m_eObjID = OBJ_ID::NPC_CITIZEN_1;
	case OBJ_ID::NPC_CITIZEN_2:
		m_iNpc = 2;
		m_eObjID = OBJ_ID::NPC_CITIZEN_2;
	case OBJ_ID::NPC_KING:
		m_iNpc = 3;
		m_eObjID = OBJ_ID::NPC_KING;
	case OBJ_ID::NPC_MAGE:
		m_iNpc = 4;
		m_eObjID = OBJ_ID::NPC_MAGE;
	case OBJ_ID::NPC_SOLLIDER:
		m_iNpc = 5;
		m_eObjID = OBJ_ID::NPC_SOLLIDER;
	case OBJ_ID::NPC_DRAKOS:
		m_iNpc = 6;
		m_eObjID = OBJ_ID::NPC_DRAKOS;
	case OBJ_ID::NPC_SPIRIT:
		m_eEmo = eEmo;
		m_eObjID = OBJ_ID::NPC_SPIRIT;
	default:
		break;
	}
}

void CDialogUI::Typing_Effect(const _float& fTimeDelta)
{
	if (m_strDialog.size() < m_iTextCnt)
		return;

	m_fAcc += fTimeDelta;

	if (0.1f < m_fAcc)
	{
		m_strTyping += m_strDialog[m_iTextCnt];
		m_iTextCnt++;

		m_fAcc = m_fAcc - 0.1f;
	}
}

CDialogUI* CDialogUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, OBJ_ID eNpc, wstring strDialog, SPIRITEMO_TYPE eEmo)
{
	CDialogUI* pInstance = new CDialogUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("DialogUI Create Failed");
		return nullptr;
	}
	if (FAILED(pInstance->Ready_Dialog(eNpc, strDialog, eEmo)))
	{
		Safe_Release(pInstance);

		MSG_BOX("DialogUI Create Failed");
		return nullptr;
	}
	

	return pInstance;
}

void CDialogUI::Free()
{
	__super::Free();

}
