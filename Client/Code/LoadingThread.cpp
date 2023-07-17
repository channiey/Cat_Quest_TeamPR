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
	case Engine::LOADING_THREAD_TYPE::COMPONENT_AND_TEXTURE:
	{
		iFlag = pLoading->Loading_For_ComponentAndTexture();
	}
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

_uint CLoadingThread::Loading_For_ComponentAndTexture()
{
#pragma region Component

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::CAMERA,
		CCamera::Create(m_pGraphicDev, &g_hWnd)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::TRANSFORM,
		CTransform::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::STATEMACHINE,
		CStateMachine::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::ANIMATOR,
		CAnimator::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::AICOM,
		CAIComponent::Create(m_pGraphicDev)), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::RIGIDBODY,
		CRigidBody::Create(m_pGraphicDev)), E_FAIL);

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

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_SPHERE,
		CSphereCollider::Create(m_pGraphicDev)), E_FAIL);


#pragma endregion


#pragma region Texture


#pragma region KANG


	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_GW",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain_World.png")), E_FAIL);

 	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_IW",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/IceWorld.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_ID",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/IceDungeon.png")), E_FAIL);

#pragma region Building

	// House
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_4.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House5",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_5.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House6",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_6.png")), E_FAIL);

	// KingHouse
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_KingHouse_In",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/capital_city_interior.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_KingHouse_Out",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/capital_city.png")), E_FAIL);

	// Smithy
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Smithy",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/kit_cat_smithy.png")), E_FAIL);

	// Magic Shop
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_MagicShop",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/arcane_temples.png")), E_FAIL);


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

	// ===============================================================
	
	// ============================= NPC =============================
#pragma region NPC

	// King
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_King",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/King/%d.png", 8)), E_FAIL);

	// Mage
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/Mage/%d.png", 8)), E_FAIL);

	// BlackSmith
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_BlackSmith",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/Smith/%d.png", 8)), E_FAIL);

	// Soldier
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Soldier",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/Soldier/%d.png", 8)), E_FAIL);

	// Citizen1
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Citizen1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/TownNpc1/%d.png", 8)), E_FAIL);

	// Citizen2
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Citizen2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/TownNpc2/%d.png", 8)), E_FAIL);


#pragma endregion
	// ===============================================================

	// =========================== Effect ============================
#pragma region EFFECT

	// 구름 
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_3.png")), E_FAIL);

	// 구름 그림자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud1_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_1_shadow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud3_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_2_shadow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud2_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_3_shadow.png")), E_FAIL);

	// 플레이어 이동 효과
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Move_Dust",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/dust/%d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Move_Water",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/watersplash/%d.png", 4)), E_FAIL);

	// 그림자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Shadow_Creature",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Shadow/cat_shadow.png")), E_FAIL);

	// 꽃가루
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Pollen",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Pollen/Pollen.png")), E_FAIL);

	// 아이템 반짝이
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_ItemSparkle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Item/Sparkle.png")), E_FAIL);

	// 몬스터스피릿
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_MonsterSpirit",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/MonsterSpirit.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Spiritorb",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/spiritorb.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Spiritwave",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/spiritwave.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Yelloworbs",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/yelloworbs.png")), E_FAIL);


#pragma endregion

#pragma endregion

#pragma region KIM

	// Monster - test - CuteMonster
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
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/Back/Attack/%d.png", 6)), E_FAIL);


	// Monster - Hedgehog
 	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Hedgehog",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/hedgehog.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/hedgehog_back.png")), E_FAIL);

	// Monster - Bat
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Bat",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Front/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Bat",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Back/%d.png", 4)), E_FAIL);

	// Monster - Ram
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Ram",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/ram.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Ram",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/ram_back.png")), E_FAIL);


	// Monster - Fox
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Fox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fox/fox.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Fox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fox/fox_back.png")), E_FAIL);


	// Monster - Wyvern
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Wyvern",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Front/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Wyvern",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Back/%d.png", 4)), E_FAIL);

	// Monster - Squirrel
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Squirrel",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Squirrel/squirrel.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Squirrel",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Squirrel/squirrel_back.png")), E_FAIL);


	// Item ====

	//  Item - Gold
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_Gold",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Object/Gold.png")), E_FAIL);

	// Item - Exp
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_Exp",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Object/Exp.png")), E_FAIL);

	// Item - Key
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_Key",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Object/Key.png")), E_FAIL);

	// Item - Warrior Weapon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_WarriorWeapon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Weapon/thorns_weapon.png")), E_FAIL);
		

	// Item - Mage Weapon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_MageWeapon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Weapon/mage_weapon.png")), E_FAIL);

	// Item - Ninja Weapon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_NinjaWeapon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Weapon/ninja_weapon.png")), E_FAIL);


	// Inventory ====
	// Inventory - BackGround
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_BKG",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/white_bg.png")), E_FAIL);

	// Inventory - Tab Button
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Tab",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_tab.png")), E_FAIL);

	// Inventory - Tab Armors Texture
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Tab_Armors_Texture",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_armors.png")), E_FAIL);

	// Inventory - Tab Skill Texture
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Tab_Skill_Texture",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_attackskill.png")), E_FAIL);

	// Inventory - UI Blank Button
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button_blank",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_blank_button.png")), E_FAIL);

	// Inventory - UI Button
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button.png")), E_FAIL);
	
	//Inventory - UI Button Gold
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button_Gold",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_gold.png")), E_FAIL);

	// Inventory - UI button Plain
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button_Plain",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_plain.png")), E_FAIL);

	// Inventory - UI Cancel 
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button_Cancel",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_cancel.png")), E_FAIL);

	// Inventory - UI Line
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Line",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_line4px.png")), E_FAIL);



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

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Enter",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Enter/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Bar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Bar/%d.png", 11)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Indicator",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Indicator.png")), E_FAIL);
	// 쉐이드느낌
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Shade",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Shade.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Dropshade",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Dropshade.png")), E_FAIL);
	//  스킬
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Skill",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Skill/%d.png", 7)), E_FAIL);
	// 마나서클
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_MpCircle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/MpCircle.png")), E_FAIL);
	// 작은화살표
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SmallArrow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SmallArrow.png")), E_FAIL);
	// 다이얼로그 박스
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SpeechBox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SpeechBox.png")), E_FAIL);
	// 다이얼로그 화살표
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_ScrollArrow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/ScrollArrow/%d.png", 3)), E_FAIL);
	// NPC스탠드
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_NpcStand",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/NpcStand/%d.png", 7)), E_FAIL);
	// 스피릿스탠드
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SpiritStand",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SpiritStand/%d.png", 5)), E_FAIL);


#pragma endregion

#pragma region YUN

	// 이펙트-스킬-캐스트

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Fire",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Fire/%d.png", 29)), E_FAIL); // 파이어 테스트

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Thunder",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Thunder/%d.png", 11)), E_FAIL); // 썬더 테스트

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Ice",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Ice/%d.png", 13)), E_FAIL); // 썬더 테스트
#pragma endregion


#pragma endregion

	m_bFinish = true;

	return 0;
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

