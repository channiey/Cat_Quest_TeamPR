#include "stdafx.h"
#include "..\Header\Scene_Intro.h"

#include "Export_Function.h"

#include "LoadingThread.h"
#include "Scene_World.h"
#include "Scene_Tool.h"
#include "BackGround.h"
#include "SoundMgr.h"

CScene_Intro::CScene_Intro(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::INTRO)
	, m_pLoading(nullptr)
{
}

CScene_Intro::~CScene_Intro()
{
}

HRESULT CScene_Intro::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(), E_FAIL);

	// 컴포넌트 및 텍스처 로딩 쓰레드 생성
	m_pLoading = CLoadingThread::Create(m_pGraphicDev, LOADING_THREAD_TYPE::COMPONENT_AND_TEXTURE);

	NULL_CHECK_RETURN(m_pLoading, E_FAIL);

	CSoundMgr::GetInstance()->Initialize();

	// 동영상 
	m_hVideo = MCIWndCreate(g_hWnd,			// 부모 윈도우 핸들
		nullptr,		// mci 윈도우를 사용하는 인스턴스 핸들
		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD : 자식 창, WS_VISIBLE : 그 즉시 화면에 시연, MCIWNDF_NOPLAYBAR : 플레이 바를 생성하지 않음
		L"../Bin/Resource/Video/intro.wmv");	// 재생할 파일의 경로

									//MoveWindow : 동영상을 재생할 크기를 설정
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);

	// 백버퍼 생성
	if (FAILED(m_pGraphicDev->CreateRenderTarget(WINCX, WINCY, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pBackBuffer, nullptr)))
		return E_FAIL;

	return S_OK;
}

Engine::_int CScene_Intro::Update_Scene(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Scene(fTimeDelta);

	if (TRUE == m_pLoading->Get_Finish())
	{
		CScene* pScene = nullptr;

		if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())
		{
			pScene = CScene_World::Create(m_pGraphicDev);
			CEventMgr::GetInstance()->Change_Scene(pScene);
		}
		else if ((PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode()))
		{
			pScene = CScene_Tool::Create(m_pGraphicDev);
			FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);
		}

		NULL_CHECK_RETURN(pScene, -1);
	}

	return iExit;
}

void CScene_Intro::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CScene_Intro::Render_Scene()
{
#pragma region Stack

	RECT	rc{};
	_vec3	vPos{};
	CGameObject* pObj = nullptr;
	TCHAR	szBuf[MAX_STR] = L"";
	GetClientRect(g_hWnd, &rc);

#pragma endregion

	if (true == m_pLoading->Get_Finish())
		swprintf_s(szBuf, L"로딩 완료! 스페이스바 입력!.                                                                                    .");
	else
		swprintf_s(szBuf, L"로딩 중...                                                                 .");

	SCREEN_MSG(szBuf, rc);
}

void CScene_Intro::Free()
{
	Safe_Release(m_pLoading);
	MCIWndClose(m_hVideo);
	Safe_Release(m_pBackBuffer); // 백버퍼 해제
	__super::Free();
}

CScene_Intro* CScene_Intro::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Intro* pInstance = new CScene_Intro(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Logo Create Failed");
		return nullptr;
	}

	return pInstance;
}

HRESULT CScene_Intro::Ready_Prototype()
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, CRcTex::Create(m_pGraphicDev)), E_FAIL);

	return S_OK;
}

HRESULT CScene_Intro::Ready_Layer_Environment()
{
	return S_OK;
}

