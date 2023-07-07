#include "stdafx.h"
#include "..\Header\LoadingThread.h"
#include "Export_Function.h"

CLoadingThread::CLoadingThread(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	m_pGraphicDev->AddRef();
}


CLoadingThread::~CLoadingThread()
{

}

unsigned int CLoadingThread::Thread_Main(void * pArg)
{
	CLoadingThread*		pLoading = reinterpret_cast<CLoadingThread*>(pArg);

	_uint	iFlag = 0;

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case Engine::LOADING_THREAD_TYPE::STAGE:
		iFlag = pLoading->Loading_For_World();
		break;
	case Engine::LOADING_THREAD_TYPE::TOOL:
		iFlag = pLoading->Loading_For_Tool();
		break;
	case Engine::LOADING_THREAD_TYPE::TYPEEND:
		break;
	default:
		break;
	}

	LeaveCriticalSection(pLoading->Get_Crt());

	return iFlag;
}

HRESULT CLoadingThread::Ready_Loading(LOADING_THREAD_TYPE eLoadingID)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);

	m_eID = eLoadingID;

	return S_OK;
}

_uint CLoadingThread::Loading_For_World()
{
#pragma region Default

	// Camera
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::CAMERA,
		CCamera::Create(m_pGraphicDev, &g_hWnd)), E_FAIL);

	// Transform
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::TRANSFORM,
		CTransform::Create(m_pGraphicDev)), E_FAIL);

	// Vertex
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_TEX,
		CTerrainTex::Create(m_pGraphicDev)), E_FAIL);

	// Collider
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_LINE,
		CLineCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_CIRCLE,
		CCircleCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_RECT,
		CRectCollider::Create(m_pGraphicDev)), E_FAIL);


#pragma endregion


#pragma region Texture

	// Texture
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Tile0.jpg")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/cutscene_intro_drakoth_01.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Monster",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/cutscene_intro_sister_01.png")), E_FAIL);

#pragma region KANG

#pragma endregion

#pragma region KIM

	// UI - Level
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Level",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/UI_Level.png")), E_FAIL);



#pragma endregion

#pragma region LEE

#pragma endregion

#pragma region YUN

#pragma endregion

#pragma endregion



	m_bFinish = true;

	return 0;
}

_uint CLoadingThread::Loading_For_Tool()
{
#pragma region Default

	// Camera
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::CAMERA,
		CCamera::Create(m_pGraphicDev, &g_hWnd)), E_FAIL);

	// Transform
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::TRANSFORM,
		CTransform::Create(m_pGraphicDev)), E_FAIL);

	// Vertex
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_TEX,
		CTerrainTex::Create(m_pGraphicDev)), E_FAIL);

	// Collider
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_LINE,
		CLineCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_CIRCLE,
		CCircleCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_RECT,
		CRectCollider::Create(m_pGraphicDev)), E_FAIL);


#pragma endregion


#pragma region Texture

	// Texture
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Tile0.jpg")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/cutscene_intro_drakoth_01.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Monster",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/cutscene_intro_sister_01.png")), E_FAIL);

#pragma region KANG

#pragma endregion

#pragma region KIM

#pragma endregion

#pragma region LEE

#pragma endregion

#pragma region YUN

#pragma endregion

#pragma endregion



	m_bFinish = true;

	return 0;
}
_uint CLoadingThread::Loading_For_Boss()
{
	return _uint();
}

CLoadingThread * CLoadingThread::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADING_THREAD_TYPE eID)
{
	CLoadingThread*		pInstance = new CLoadingThread(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eID)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Loading Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLoadingThread::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}

