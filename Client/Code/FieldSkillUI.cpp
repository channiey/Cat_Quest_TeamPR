#include "stdafx.h"
#include "FieldSkillUI.h"
#include "Export_Function.h"

#include "RingUI.h"

CFieldSkillUI::CFieldSkillUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_FILEDSKILL)
	, m_bIsOn(false)
{
}

CFieldSkillUI::CFieldSkillUI(const CFieldSkillUI& rhs)
	: CUI(rhs)
{
}

CFieldSkillUI::~CFieldSkillUI()
{
}

HRESULT CFieldSkillUI::Ready_Object()
{
	//m_rcUI[0] = { long(m_fPosX - m_fSizeX / 2.f) , long(m_fPosY - m_fSizeY / 2.f) , long(m_fPosX + m_fSizeX / 2.f) , long(m_fPosY + m_fSizeY / 2.f) };
	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV1;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bShirnk = true;
	/*for (auto iter : m_bReach)
		iter = false;
	for (auto iter : m_bPick)
		iter = false;*/

	// 쉐이드 설정
	D3DXMatrixIdentity(&m_UImatWorld);
	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY >> 1;
	m_fSizeX = WINCX;
	m_fSizeY = WINCY;
	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;
	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;
	

	for (_uint i = 0; i < 17; ++i)
	{
		D3DXMatrixIdentity(&m_matWorldUI[i]);
	}
	// 큰링설정 200.f 192.f
	m_RingPosX[0] = WINCX * 0.5f;
	m_RingPosY[0] = WINCY * 0.5f;
	m_RingSizeX[0] = 320.f;
	m_RingSizeY[0] = 306.4f;
	m_matWorldUI[0]._41 = m_RingPosX[0];
	m_matWorldUI[0]._42 = m_RingPosY[0];
	m_matWorldUI[0]._11 = m_RingSizeX[0];
	m_matWorldUI[0]._22 = m_RingSizeY[0];

	// 스킬1
	m_SkillPosX[0] = WINCX * 0.5f;
	m_SkillPosY[0] = WINCY * 0.82f;
	m_SkillSizeX = 74.25f;
	m_SkillSizeY = 74.25f;
	m_matWorldUI[1]._41 = m_SkillPosX[0];
	m_matWorldUI[1]._42 = m_SkillPosY[0];
	m_matWorldUI[1]._11 = m_SkillSizeX;
	m_matWorldUI[1]._22 = m_SkillSizeY;

	// 스킬2
	m_SkillPosX[1] = WINCX * 0.69f;
	m_SkillPosY[1] = WINCY * 0.5f;
	m_matWorldUI[2]._41 = m_SkillPosX[1];
	m_matWorldUI[2]._42 = m_SkillPosY[1];
	m_matWorldUI[2]._11 = m_SkillSizeX;
	m_matWorldUI[2]._22 = m_SkillSizeY;

	// 스킬3
	m_SkillPosX[2] = WINCX * 0.31f;
	m_SkillPosY[2] = WINCY * 0.5f;
	m_matWorldUI[3]._41 = m_SkillPosX[2];
	m_matWorldUI[3]._42 = m_SkillPosY[2];
	m_matWorldUI[3]._11 = m_SkillSizeX;
	m_matWorldUI[3]._22 = m_SkillSizeY;

	// 스킬4
	m_SkillPosX[3] = WINCX * 0.5f;
	m_SkillPosY[3] = WINCY * 0.18f;
	m_matWorldUI[4]._41 = m_SkillPosX[3];
	m_matWorldUI[4]._42 = m_SkillPosY[3];
	m_matWorldUI[4]._11 = m_SkillSizeX;
	m_matWorldUI[4]._22 = m_SkillSizeY;

	// 마나링1
	m_ManaSizeX = 30.f;
	m_ManaSizeY = 34.f;
	m_matWorldUI[5]._41 = m_SkillPosX[0];
	m_matWorldUI[5]._42 = m_SkillPosY[0] - 75;
	m_matWorldUI[5]._11 = m_ManaSizeX;
	m_matWorldUI[5]._22 = m_ManaSizeY;
	// 마나링2
	m_matWorldUI[6]._41 = m_SkillPosX[1];
	m_matWorldUI[6]._42 = m_SkillPosY[1] - 75;
	m_matWorldUI[6]._11 = m_ManaSizeX;
	m_matWorldUI[6]._22 = m_ManaSizeY;
	// 마나링3
	m_matWorldUI[7]._41 = m_SkillPosX[2];
	m_matWorldUI[7]._42 = m_SkillPosY[2] - 75;
	m_matWorldUI[7]._11 = m_ManaSizeX;
	m_matWorldUI[7]._22 = m_ManaSizeY;
	// 마나링4
	m_matWorldUI[8]._41 = m_SkillPosX[3];
	m_matWorldUI[8]._42 = m_SkillPosY[3] - 75;
	m_matWorldUI[8]._11 = m_ManaSizeX;
	m_matWorldUI[8]._22 = m_ManaSizeY;

	// 작은링 1
	m_RingSizeX[1] = 90.f;
	m_RingSizeY[1] = 86.175f;
	m_matWorldUI[9]._41 = m_SkillPosX[0];
	m_matWorldUI[9]._42 = m_SkillPosY[0];
	m_matWorldUI[9]._11 = m_RingSizeX[1];
	m_matWorldUI[9]._22 = m_RingSizeY[1];
	// 작은링 2
	m_matWorldUI[10]._41 = m_SkillPosX[1];
	m_matWorldUI[10]._42 = m_SkillPosY[1];
	m_matWorldUI[10]._11 = m_RingSizeX[1];
	m_matWorldUI[10]._22 = m_RingSizeY[1];
	// 작은링 3
	m_matWorldUI[11]._41 = m_SkillPosX[2];
	m_matWorldUI[11]._42 = m_SkillPosY[2];
	m_matWorldUI[11]._11 = m_RingSizeX[1];
	m_matWorldUI[11]._22 = m_RingSizeY[1];
	// 작은링 4
	m_matWorldUI[12]._41 = m_SkillPosX[3];
	m_matWorldUI[12]._42 = m_SkillPosY[3];
	m_matWorldUI[12]._11 = m_RingSizeX[1];
	m_matWorldUI[12]._22 = m_RingSizeY[1];


	return S_OK;
}

_int CFieldSkillUI::Update_Object(const _float& fTimeDelta)
{

	_int iExit = __super::Update_Object(fTimeDelta);

	Mouse_Input();

	if (m_bIsOn)
	{
		if (m_bShirnk)
		{
			_vec3 vOut = m_pUITransform[0]->Lerp(_vec3{ m_RingSizeX[0] , m_RingSizeY[0], 0.f }, _vec3{ 240.f , 230.f, 0.f }, 0.1f, fTimeDelta);
			if (vOut.x != -99)
			{
				m_matWorldUI[0]._11 = vOut.x;
				m_matWorldUI[0]._22 = vOut.y;
			}
			else
				m_bShirnk = false;
		}
	}
	
	return iExit;
}

void CFieldSkillUI::LateUpdate_Object()
{

	if (m_bIsOn)
	{
		

		

		__super::LateUpdate_Object();
	}
	
}

void CFieldSkillUI::Render_Object()
{

	if (m_bIsOn)
	{
	
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);
		// 쉐이드 비스무리
		m_pTextureCom->Render_Texture();
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(128, 255, 255, 255));
		// 큰링
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[0]);
		m_pUITextureCom[0]->Render_Texture();
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

		if (!m_bShirnk)
		{

			// 작은링1
			if (m_bPick[0])
			{
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[9]);
				m_pUITextureCom[0]->Render_Texture();
				m_pBufferCom->Render_Buffer();
			}
			// 작은링2
			if (m_bPick[1])
			{
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[10]);
				m_pUITextureCom[0]->Render_Texture();
				m_pBufferCom->Render_Buffer();
			}
			// 작은링3
			if (m_bPick[2])
			{
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[11]);
				m_pUITextureCom[0]->Render_Texture();
				m_pBufferCom->Render_Buffer();
			}
			if (m_bPick[3])
			{
				// 작은링4
				m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[12]);
				m_pUITextureCom[0]->Render_Texture();
				m_pBufferCom->Render_Buffer();
			}
			

			// 스킬1
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[1]);
			m_pUITextureCom[2]->Render_Texture(0);
			m_pBufferCom->Render_Buffer();
			// 스킬2
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[2]);
			m_pUITextureCom[2]->Render_Texture(4);
			m_pBufferCom->Render_Buffer();
			// 스킬3
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[3]);
			m_pUITextureCom[2]->Render_Texture(2);
			m_pBufferCom->Render_Buffer();
			// 스킬4
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[4]);
			m_pUITextureCom[2]->Render_Texture(1);
			m_pBufferCom->Render_Buffer();
			// 마나링1
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[5]);
			m_pUITextureCom[3]->Render_Texture();
			m_pBufferCom->Render_Buffer();
			// 마나링2
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[6]);
			m_pUITextureCom[3]->Render_Texture();
			m_pBufferCom->Render_Buffer();
			// 마나링3
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[7]);
			m_pUITextureCom[3]->Render_Texture();
			m_pBufferCom->Render_Buffer();
			// 마나링4
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorldUI[8]);
			m_pUITextureCom[3]->Render_Texture();
			m_pBufferCom->Render_Buffer();
			
			

		}
		

		__super::Render_Object();
	
	}
}

void CFieldSkillUI::Picking_UI()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	pt.y = WINCY - pt.y;

}

void CFieldSkillUI::Mouse_Input()
{
	if (CInputDev::GetInstance()->Get_DIMouseState(DIM_RB))
	{
		m_bIsOn = true;
		
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(false);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(false);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::EFFECT)->Layer_SetActive(false);

		CRingUI* pRingUI = static_cast<CRingUI*>
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Ring"));
		pRingUI->Set_Active(false);

		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 235, 168, 35));
	}
	else
	{
		m_bIsOn = false;
		
		Ready_Object();

		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(true);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::EFFECT)->Layer_SetActive(true);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(true);

		CRingUI* pRingUI = static_cast<CRingUI*>
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Ring"));
		pRingUI->Set_Active(true);

	}
}

HRESULT CFieldSkillUI::Add_Component()
{

	CComponent* pComponent = nullptr;
	// 메인
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Shade", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	// 서브
	pComponent = m_pUITextureCom[0] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Ring", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[1] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_SmallArrow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[2] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Skill", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom[3] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_MpCircle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	for (_uint i = 0; i < 5; ++i)
	{
		pComponent = m_pUITransform[i] = dynamic_cast<CTransform*>(Engine::Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	}


	return S_OK;
}

CFieldSkillUI* CFieldSkillUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFieldSkillUI* pInstance = new CFieldSkillUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FieldSkillUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFieldSkillUI::Free()
{
	__super::Free();

}
