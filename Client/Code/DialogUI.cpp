#include "DialogUI.h"
#include "Export_Function.h"

#include "Player.h"

CDialogUI::CDialogUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev, OBJ_ID::UI_DIALOG), m_bEnd(false)
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
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV1;

	D3DXMatrixIdentity(&m_UImatWorld);
	for (_uint i = 0; i < 2; ++i)
	{
		D3DXMatrixIdentity(&m_matUI[i]);
	}

	// ó�� ������� ��ġ
	m_fPosX = WINCX * 0.45;
	m_fPosY = WINCY * 0.2;
	m_fSizeX =  400;
	m_fSizeY =  124;
	// �ؽ�Ʈ������ ��ġ�� ������
	m_rcText = { long(m_fPosX - (m_fSizeX / 2.f) - 80) , long(WINCY - m_fPosY - (m_fSizeY / 2.f)) - 20,
		long(m_fPosX + (m_fSizeX / 2.f) + 70) , long(WINCY - m_fPosY + m_fSizeY / 2.f) - 20 };
	// ����ġ�ڽ��� �ʱ� ����
	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;
	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	return S_OK;
}

_int CDialogUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Typing_Effect(fTimeDelta);

	_float fReach = 1.f;
	if (m_bDown)
	{
		_vec3 vOut = m_pTransformCom->Lerp(_vec3{ m_matUI[0]._41, m_matUI[0]._42, 0.f }
		, _vec3{ m_matUI[0]._41, m_matUI[0]._42 - fReach, 0.f }, 0.12f, fTimeDelta);
		if (vOut.x != -99)
		{
			m_matUI[0]._42 = vOut.y;
		}
		else
		{
			m_bDown = false;
			m_bUp = true;
		}
			
	}
	if (m_bUp)
	{
		_vec3 vOut = m_pTransformCom->Lerp(_vec3{ m_matUI[0]._41, m_matUI[0]._42, 0.f }
		, _vec3{ m_matUI[0]._41, m_matUI[0]._42 + fReach, 0.f }, 0.12f, fTimeDelta);
		if (vOut.x != -99)
		{
			m_matUI[0]._42 = vOut.y;
		}
		else
		{
			m_bDown = true;
			m_bUp = false;
		}
	}
	_float fScale = 0.8f;
	if (m_bExpand)
	{
		_vec3 vOut = m_pUITransform->Lerp(_vec3{ m_matUI[1]._11, m_matUI[1]._22, 0.f }
		, _vec3{ m_matUI[1]._11, m_matUI[1]._22 + fScale, 0.f }, 0.6f, fTimeDelta);
		if (vOut.x != -99)
		{
			m_matUI[1]._22 = vOut.y;
		}
		else
		{
			m_bExpand = false;
		}

	}
	if (!m_bExpand)
	{
		_vec3 vOut = m_pUITransform->Lerp(_vec3{ m_matUI[1]._11, m_matUI[1]._22, 0.f }
		, _vec3{ m_matUI[1]._11, m_matUI[1]._22 - fScale, 0.f }, 0.6f, fTimeDelta);
		if (vOut.x != -99)
		{
			m_matUI[1]._22 = vOut.y;
		}
		else
		{
			m_bExpand = true;
		}

	}
	

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

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[0]);
	m_pUITextureCom[0]->Render_Texture(2);
	m_pBufferCom->Render_Buffer();

	if (m_eObjID != OBJ_ID::NPC_SPIRIT)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[1]);
		m_pUITextureCom[1]->Render_Texture(m_iNpc);
		m_pBufferCom->Render_Buffer();
	}
	

	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_strTyping.c_str(), -1,
		&m_rcText, DT_LEFT | DT_WORDBREAK, D3DCOLOR_ARGB(200, 0, 0, 0));

	// �ؽ�Ʈ�ڽ� �׽�Ʈ��Ʈ
	/*HDC hDC = GetDC(g_hWnd);
	Rectangle(hDC, m_rcText.left, m_rcText.top, m_rcText.right, m_rcText.bottom);*/

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

	pComponent = m_pUITransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);


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
	m_fAcc = 0.f;
	m_iTextCnt = 0.f;

	// �� ���̾�α� ���̿� ���� �ؽ�Ʈ�ڽ�ũ�� ����
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_strDialog.c_str(), -1,
		&m_rcText, DT_LEFT | DT_CALCRECT | DT_WORDBREAK, D3DCOLOR_ARGB(200, 0, 0, 0));

	if (m_rcText.bottom >= 750)
	{
		m_rcText.top -= 160;
		m_rcText.bottom -= 160;
	}
	if (m_rcText.bottom >= 650)
	{
		m_rcText.top -= 60;
		m_rcText.bottom -= 60;
	}
	

	// ����� ũ�⸦ ������ ����ġ�ڽ� �缳��
	_int textWidth = m_rcText.right - m_rcText.left;
	_int textHeight = m_rcText.bottom - m_rcText.top;

	m_fSizeY = _float(textHeight);
	m_fPosY = (_float(m_rcText.top) + _float(m_rcText.bottom)) / 2.f;

	

	m_UImatWorld._42 = WINCY - m_fPosY - 10;
	m_UImatWorld._22 = m_fSizeY;

	// �̿����� ȭ��ǥ ����
	m_matUI[0]._41 = m_UImatWorld._41 + 280;
	m_matUI[0]._42 = (m_UImatWorld._42 - (m_UImatWorld._22 / 2.f) + 5);
	m_matUI[0]._11 = 20.8f;
	m_matUI[0]._22 = 12.4f;
	m_bDown = true;
	m_bUp = false;

	// �̿����� ȭ�� �ؽ�ó ����
	m_matUI[1]._41 = m_UImatWorld._41 + 420;
	m_matUI[1]._42 = (m_UImatWorld._42 - (m_UImatWorld._22 / 2.f) + 100);
	m_matUI[1]._11 = 120.f;
	m_matUI[1]._22 = 188.f;
	m_bExpand = true;
	m_bShrink = false;


	return S_OK;
}

void CDialogUI::Select_Npc(OBJ_ID eNpc, SPIRITEMO_TYPE eEmo)
{
	switch (eNpc)
	{
		case OBJ_ID::NPC_BLACKSMITH:
			m_iNpc = 0;
			m_eObjID = OBJ_ID::NPC_BLACKSMITH;
			break;
		case OBJ_ID::NPC_CITIZEN_1:
			m_iNpc = 1;
			m_eObjID = OBJ_ID::NPC_CITIZEN_1;
			break;
		case OBJ_ID::NPC_CITIZEN_2:
			m_iNpc = 2;
			m_eObjID = OBJ_ID::NPC_CITIZEN_2;
			break;
		case OBJ_ID::NPC_KING:
			m_iNpc = 3;
			m_eObjID = OBJ_ID::NPC_KING;
			break;
		case OBJ_ID::NPC_MAGE:
			m_iNpc = 4;
			m_eObjID = OBJ_ID::NPC_MAGE;
			break;
		case OBJ_ID::NPC_SOLLIDER:
			m_iNpc = 5;
			m_eObjID = OBJ_ID::NPC_SOLLIDER;
			break;
		case OBJ_ID::NPC_DRAKOS:
			m_iNpc = 6;
			m_eObjID = OBJ_ID::NPC_DRAKOS;
			break;
		case OBJ_ID::NPC_SPIRIT:
			m_eEmo = eEmo;
			m_eObjID = OBJ_ID::NPC_SPIRIT;
			break;
		default:
			break;
	}
}

void CDialogUI::Typing_Effect(const _float& fTimeDelta)
{
	if (m_strDialog.size() < m_iTextCnt)
	{
		m_bEnd = true;
		return;
	}
		

	m_fAcc += fTimeDelta;

	if (0.05f < m_fAcc)
	{
		m_strTyping += m_strDialog[m_iTextCnt];
		m_iTextCnt++;

		m_fAcc = m_fAcc - 0.05f;
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