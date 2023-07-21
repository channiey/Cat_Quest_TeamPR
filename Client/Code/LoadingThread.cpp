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


	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_World",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain_World.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_Dungeon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain_Dungeon.png")), E_FAIL);

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

	// ȭ��ǰ ����
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Cosmetic_Chest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Chest/chest_cosmetic.png")), E_FAIL);
	// Ȳ�� ����
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Gold_Chest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Chest/chest_gold.png")), E_FAIL);
	// �⺻ ����
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

	// ���� 
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_3.png")), E_FAIL);

	// ���� �׸���
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud1_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_1_shadow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud3_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_2_shadow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud2_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_3_shadow.png")), E_FAIL);

	// �÷��̾� �̵� ȿ��
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Move_Dust",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/dust/%d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Move_Water",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/watersplash/%d.png", 4)), E_FAIL);

	// �׸���
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Shadow_Creature",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Shadow/cat_shadow.png")), E_FAIL);

	// �ɰ���
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Pollen",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Pollen/Pollen.png")), E_FAIL);

	// ������ ��¦��
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_ItemSparkle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Item/Sparkle.png")), E_FAIL);

	// ���ͽ��Ǹ�
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_MonsterSpirit",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/MonsterSpirit.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Spiritorb",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/spiritorb.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Spiritwave",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/spiritwave.png")), E_FAIL);

	// �÷��̾� ������
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Player_Slash_Rising",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/PlayerSlash/Rising/%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Player_Slash_Chopping",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/PlayerSlash/Chopping/%d.png", 4)), E_FAIL);

	// ���� �ǰ�
	// ��
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Monster_Cut_Effect",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/CutEffect/CutEffect.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Monster_CutOrb_Effect",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/CutEffect/CutOrb.png")), E_FAIL);

// ===============================================================

// =========================== Inventory ============================
#pragma region Inventory
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

	// Inventory - UI TabLine
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Line",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_line.png")), E_FAIL);

	// Inventory - UI TabLine
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_TabLine",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_line4px.png")), E_FAIL);

	// Inventory - UI WeaponSelect
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Weapon_Select",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_equipped_weapon.png")), E_FAIL);

	// Inventory - UI Ok
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_OK",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_OK.png")), E_FAIL);

	// Inventory - UI No
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_NO",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_NO.png")), E_FAIL);

	// Inventory - UI Player
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Gold",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_iconGold.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_HpBar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_HpBar.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_MpBar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_MpBar.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Armor",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_statDef.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Heart",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_statHeart #145685.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Damage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_statDamage.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Magic",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_statMagic.png")), E_FAIL);


#pragma endregion

#pragma endregion

#pragma region KIM

	// Monster - test - CuteMonster
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Monster",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/cutscene_intro_sister_01.png")), E_FAIL);

	//// Monster - Bat
	//FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bat",
	//	CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/bat_idle1.png")), E_FAIL);

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
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Basic/Front/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Basic/Back/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Hedgehog_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Attack/Front/%d.png", 19)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Attack/Back/%d.png", 19)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog_Stemp",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/All/groundwave/basic_shockwave.png")), E_FAIL);


	// Monster - Bat
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Bat",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Basic/Front/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Bat",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Basic/Back/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Bat_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Attack/Front/%d.png", 8)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Bat_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Attack/Back/%d.png", 8)), E_FAIL);



	// Monster - Ram
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Ram",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/Basic/Front/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Ram",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/Basic/Back/0.png")), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Ram_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/Attack/Front/%d.png", 19)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Ram_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/Attack/Back/%d.png", 19)), E_FAIL);


	// Monster - Wyvern
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Wyvern",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Basic/Front/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Wyvern",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Basic/Back/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Wyvern_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Attack/Front/%d.png", 9)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Wyvern_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Attack/Back/%d.png", 9)), E_FAIL);




	// Monster - Fox
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Fox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fox/Front/%d.png",1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Fox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fox/Back/%d.png",1)), E_FAIL);


	// Monster - Squirrel
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Squirrel",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Squirrel/Front/%d.png",1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Squirrel",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Squirrel/Back/%d.png",1)), E_FAIL);



	// Monster - Wyvern Red
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_WyvernRed",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/WyvernRed/Basic/Front/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_WyvernRed",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/WyvernRed/Basic/Back/%d.png",4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_WyvernRed_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/WyvernRed/Attack/Front/%d.png", 9)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_WyvernRed_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/WyvernRed/Attack/Back/%d.png", 9)), E_FAIL);



	// Monster - Serpent
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Serpent",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Serpent/Front/%d.png", 1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Serpent",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Serpent/Back/%d.png", 1)), E_FAIL);



	// Monster - Fish
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Fish",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fish/Front/%d.png", 1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Fish",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fish/Back/%d.png", 1)), E_FAIL);



	// Monster - Merlion
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Merlion",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Merlion/Front/%d.png", 1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Merlion",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Merlion/Back/%d.png", 1)), E_FAIL);


	// Monster - Cathulu
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Cathulu",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Cathulu/Front/%d.png", 1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Cathulu",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Cathulu/Back/%d.png", 1)), E_FAIL);


	// Boss Monster - Violet Dragon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Basic/Front/%d.png", 8)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Basic/Back/%d.png", 8)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_VioletDragon_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Attack/Front/%d.png", 18)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_VioletDragon_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Attack/Back/%d.png", 18)), E_FAIL);






	// Monster - TestMob 

	/*FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Hedgehog_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Attack/Front/%d.png" ,17 )), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Attack/Back/%d.png", 17)), E_FAIL);
*/

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

#pragma endregion

#pragma region LEE

	// �÷��̾� �ؽ�ó
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

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fDie",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Die/%d.png", 14)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWake",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Wake/%d.png", 21)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fSleep",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Sleep.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fFlight",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Flight/%d.png", 10)), E_FAIL);


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
	// ���̵����
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Shade",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Shade.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Dropshade",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Dropshade.png")), E_FAIL);
	//  ��ų
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Skill",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Skill/%d.png", 7)), E_FAIL);
	// ������Ŭ
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_MpCircle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/MpCircle.png")), E_FAIL);
	// ����ȭ��ǥ
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SmallArrow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SmallArrow.png")), E_FAIL);
	// ���̾�α� �ڽ�
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SpeechBox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SpeechBox.png")), E_FAIL);
	// ���̾�α� ȭ��ǥ
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_ScrollArrow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/ScrollArrow/%d.png", 3)), E_FAIL);
	// NPC���ĵ�
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_NpcStand",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/NpcStand/%d.png", 7)), E_FAIL);
	// ���Ǹ����ĵ�
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SpiritStand",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SpiritStand/%d.png", 5)), E_FAIL);

	// �� ����Ʈ
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Heal",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Heal/EffectHeal/%d.png", 12)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_HealPaw",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Heal/PawPink.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_HealSpark",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Heal/PawSpark.png")), E_FAIL);
	// �ö��� ��ų
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Flight",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/UI_flight.png")), E_FAIL);


#pragma endregion
	 
#pragma region YUN

	// ����Ʈ-��ų

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Fire",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/Completed/Fire/%d.png", 29)), E_FAIL); 

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Thunder",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/Completed/Thunder/%d.png", 11)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Ice",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/Completed/Ice/%d.png", 13)), E_FAIL); 
	
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Beam",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/Completed/Beam/%d.png", 20)), E_FAIL); 


	// ����Ʈ - ��ų - ���� (����)

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Big_Red",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Square_Purple.png")), E_FAIL); 

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Big_Yellow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Big_Yellow.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Attack_Circle_Red",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Attack_Red.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Arrow_Blue",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Arrow_Blue.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Arrow_Red"
			, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Arrow_Red.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Square_Purple"
			, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Square_Purple.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Square_Red"
			, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Square_Red.png")), E_FAIL);


	// ����Ʈ - ��ų - ���� (�Ϲ�)

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Ritual_Circle_Red"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Ritual_Circle_Red.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_RitualBroken_Circle_Red"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_RitualBroken_Circle_Red.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_RitualBroken_Circle_Blue"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_RitualBroken_Circle_Blue.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Ritual_Circle_Blue"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Ritual_Circle_Blue.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Small_Purple"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Small_Purple.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Small_Red"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Small_Red.png")), E_FAIL);

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

