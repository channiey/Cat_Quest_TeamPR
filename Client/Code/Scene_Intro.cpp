#include "stdafx.h"
#include "..\Header\Scene_Intro.h"

#include "Export_Function.h"

#include "LoadingThread.h"
#include "Scene_World.h"
#include "Scene_Tool.h"
#include "BackGround.h"

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

	// 로딩 쓰레드 생성
	if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode()) 
	{
		m_pLoading = CLoadingThread::Create(m_pGraphicDev, LOADING_THREAD_TYPE::COMPONENT_AND_TEXTURE);
	}
	else if ((PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode()))
	{
		m_pLoading = CLoadingThread::Create(m_pGraphicDev, LOADING_THREAD_TYPE::COMPONENT_AND_TEXTURE);
	}

	NULL_CHECK_RETURN(m_pLoading, E_FAIL);
	
	return S_OK;
}

Engine::_int CScene_Intro::Update_Scene(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Scene(fTimeDelta);

	if (TRUE == m_pLoading->Get_Finish()) 
	{
		CScene* pScene = nullptr; 

		if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())
			pScene = CScene_World::Create(m_pGraphicDev);
		else if ((PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode()))
			pScene = CScene_Tool::Create(m_pGraphicDev);

		NULL_CHECK_RETURN(pScene, -1);

		FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);
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
	CGameObject*	pObj = nullptr;
	TCHAR	szBuf[MAX_STR] = L"";
	GetClientRect(g_hWnd, &rc);

#pragma endregion

	// DT
	if (true == m_pLoading->Get_Finish())
		swprintf_s(szBuf, L"로딩 완료");
	else
		swprintf_s(szBuf, L"로딩 중");

	SCREEN_MSG(szBuf, rc);

	
}

void CScene_Intro::Free()
{
	Safe_Release(m_pLoading);

	__super::Free();
}

CScene_Intro* CScene_Intro::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Intro*	pInstance = new CScene_Intro(pGraphicDev);

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

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Logo", CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Logo/title.png")), E_FAIL);
	
	return S_OK;
}

HRESULT CScene_Intro::Ready_Layer_Environment()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	pGameObject = CBackGround::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BackGround", pGameObject), E_FAIL);

	m_mapLayer.insert({ OBJ_TYPE::BACKGROUND, pLayer });

	return S_OK;
}

