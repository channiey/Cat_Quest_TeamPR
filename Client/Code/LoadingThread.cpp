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
		iFlag = pLoading->Loading_For_World();
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

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX,
		CTerrainRcTex::Create(m_pGraphicDev)), E_FAIL);

	// Collider
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_LINE,
		CLineCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_CIRCLE,
		CCircleCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_RECT,
		CRectCollider::Create(m_pGraphicDev)), E_FAIL);

	// State Machine
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::STATEMACHINE,
		CStateMachine::Create(m_pGraphicDev)), E_FAIL);

	// Animator
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::ANIMATOR,
		CAnimator::Create(m_pGraphicDev)), E_FAIL);

	// AI
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::AICOM,
		CAIComponent::Create(m_pGraphicDev)), E_FAIL);
	
#pragma endregion


#pragma region Texture


#pragma region KANG

	// 터레인 월드
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/test2.png")), E_FAIL);

	// 건물
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Building",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/town_1.png")), E_FAIL);

	// 수풀
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Forest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Environment/GrassField/forest_3.png")), E_FAIL);

	// 산
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Mountain",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Environment/GrassField/mountains_1.png")), E_FAIL);

	// 던전
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dungeon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Environment/Dungeon/dungeon_1.png")), E_FAIL);
#pragma endregion

#pragma region KIM

	// UI - Level
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Level",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/UI_Level.png")), E_FAIL);

	// UI - Tab
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Tab",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/UI_Tab.png")), E_FAIL);

	// UI - ManaBar
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_ManaBar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/ManaBar.png")), E_FAIL);

	// Monster - Hedgehog
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Hedgehog",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/basic_hedgehog.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Monster",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/cutscene_intro_sister_01.png")), E_FAIL);

	// Monster - Bat
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bat",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/bat_idle1.png")), E_FAIL);

	// Monster - Dragon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dragon_fIdle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/Front/Idle/%d.png",5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dragon_fAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/Front/Attack/%d.png", 6)), E_FAIL);

#pragma endregion

#pragma region LEE
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fIdle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Idle/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWalk",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Walk/%d.png", 12)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fHit",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Hit/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fRoll",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Roll/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack0/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack1/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack2/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bIdle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Idle/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bWalk",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Walk/%d.png", 15)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bRoll",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Roll/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack0/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack1/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack2/%d.png", 6)), E_FAIL);

#pragma endregion

#pragma region YUN


#pragma endregion

#pragma endregion

	m_bFinish = true;

	return 0;
}

_uint CLoadingThread::Loading_For_Tool()
{
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

