#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "Engine_Define.h"
#include "Export_Function.h"
#include "Scene_Intro.h"
#include "Scene_Tool.h"

#include "EventMgr.h"

#include "ImGuiMgr.h"
#include "Calculator.h"

#include "Scene_Intro.h"
#include "Scene_Tool.h"
#include "Scene_World.h"
#include "Scene_Dungeon.h"

CMainApp::CMainApp() : m_pDeviceClass(nullptr), m_pManagementClass(nullptr)
{
	
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp(void)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL); // 디바이스 초기화

	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL); // 시작 Scene, 매니지먼트 생성
		
	return S_OK;
}

int CMainApp::Update_MainApp(const float & fTimeDelta)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/


	Engine::Update_InputDev();	 // 인풋 디바이스 업데이트

	if (CInputDev::GetInstance()->Key_Down('P'))
	{
		m_pManagementClass->Set_Debug_Toggle();
	}

	NULL_CHECK_RETURN(m_pManagementClass, -1); 
 	m_pManagementClass->Update_Scene(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	NULL_CHECK(m_pManagementClass);
	m_pManagementClass->LateUpdate_Scene();
}

void CMainApp::Render_MainApp()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);	

	Engine::Render_Begin(D3DXCOLOR(0.2f, 0.8f, 0.7f, 1.f));

	NULL_CHECK(m_pManagementClass);
	m_pManagementClass->Render_Scene(m_pGraphicDev); // 렌더러 싱글톤의 렌더 함수 호출 

	CEventMgr::GetInstance()->Update_Event(); // 이벤트 매니저 업데이트 호출

	Engine::Render_End();
}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL); // 디바이스 초기화
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();
	
	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL); // 인풋 디바이스 초기화

	(*ppGraphicDev)->SetRenderState(D3DRS_LIGHTING, TRUE); 
	(*ppGraphicDev)->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // 후면 추려내기 비활성화

	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // 텍스처 불투명화 설정코드
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE); // 텍스처 색상 설정코드
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement ** ppManagementClass)
{
	// 인트로씬 생성
	Engine::CScene* pScene = CScene_Intro::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	// 매니지먼트 생성
	FAILED_CHECK_RETURN(Engine::Create_Management(pGraphicDev, ppManagementClass), E_FAIL);
	(*ppManagementClass)->AddRef();

	FAILED_CHECK_RETURN((*ppManagementClass)->Set_Scene(pScene), E_FAIL);

	return S_OK;
}


CMainApp * CMainApp::Create()
{
	CMainApp *	pInstance = new	CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance;
		pInstance = nullptr;

		return pInstance;
	}
	
	return pInstance;
}

void CMainApp::Free()
{
	CImGuiMgr::GetInstance()->DestroyInstance();

	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pDeviceClass);
	Safe_Release(m_pManagementClass);

	Engine::Release_Utility();
	Engine::Release_System();
}
