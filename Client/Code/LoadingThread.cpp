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

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::CAMERA,
		CCamera::Create(m_pGraphicDev, &g_hWnd)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::TRANSFORM,
		CTransform::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_TEX,
		CTerrainTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX,
		CTerrainRcTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_LINE,
		CLineCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_CIRCLE,
		CCircleCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_RECT,
		CRectCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::STATEMACHINE,
		CStateMachine::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::ANIMATOR,
		CAnimator::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::AICOM,
		CAIComponent::Create(m_pGraphicDev)), E_FAIL);
	
#pragma endregion


#pragma region Texture


#pragma region KANG

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_GW",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/GrassWorld.png")), E_FAIL);

 	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_IW",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/IceWorld.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_ID",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/IceDungeon.png")), E_FAIL);

	
#pragma region Building

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/House/town_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/House/town_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/House/town_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/House/town_4.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House5",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/House/town_5.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House6",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/House/town_6.png")), E_FAIL);
#pragma endregion

#pragma region Bush

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_4.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush5",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_5.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush6",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_6.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush7",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_7.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush8",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_8.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush9",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_9.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush10",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_10.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush11",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_11.png")), E_FAIL);

#pragma endregion

#pragma region Mountain

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Mountain_Grass",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Mountain/mountains_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Mountain_Ice",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Mountain/mountains_5.png")), E_FAIL);

#pragma endregion

#pragma region Pillar

	// Rock Pillar
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock_Pillar1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/rockpillar_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock_Pillar2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/rockpillar_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock_Pillar3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/rockpillar_3.png")), E_FAIL);

	// Temple Pillar
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Temple_Pillar1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/ruinpillar_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Temple_Pillar2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/ruinpillar_2.png")), E_FAIL);

	// Ice Pillar
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Ice_Pillar1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/rockpillar_4.png")), E_FAIL);

#pragma endregion

#pragma region Rock

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Rock/rocks_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Rock/rocks_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Rock/rocks_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Rock/rocks_4.png")), E_FAIL);

#pragma endregion

#pragma region Dungeon

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dungeon_Grass",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Dungeon/dungeon_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dungeon_Ice",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Dungeon/dungeon_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dungeon_Temple",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Dungeon/dungeon_3.png")), E_FAIL);
#pragma endregion

#pragma region Tower

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Tower1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tower/Tower_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Tower2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tower/Tower_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Tower3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tower/Tower_3.png")), E_FAIL);

#pragma endregion

#pragma region Chest

	// 화장품 상자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Cosmetic_Chest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Chest/chest_cosmetic.png")), E_FAIL);
	// 황금 상자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Gold_Chest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Chest/chest_gold.png")), E_FAIL);
	// 기본 상자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Regular_Chest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Chest/chest_regular.png")), E_FAIL);
#pragma endregion

#pragma endregion

#pragma region KIM

	

	

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

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dragon_bIdle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/Back/Idle/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dragon_bAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/BAck/Attack/%d.png", 6)), E_FAIL);


	// Monster - Hedgehog
 	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Hedgehog",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/hedgehog.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/hedgehog_back.png")), E_FAIL);


#pragma endregion

#pragma region LEE

	// 플레이어 텍스처
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

	// UI
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Ring",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Ring.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Zoom",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Zoom/%d.png", 2)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Tab",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Level",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/UI_Level.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Bar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Bar/%d.png", 8)), E_FAIL);


#pragma endregion

#pragma region YUN

#pragma region Skill Effect

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_skillrange_orange",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/range/skillrange_orange.png")), E_FAIL);

#pragma endregion


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

