#include "stdafx.h"
#include "..\Header\Scene_World.h"

#include "Export_Function.h"

#include "Terrain.h"
#include "TerrainWorld.h"
#include "Bush.h"
#include "Mountain.h"
#include "Dungeon.h"
// 빌딩
#include "House1.h"
#include "House2.h"
#include "House3.h"
#include "House4.h"
#include "House5.h"
#include "House6.h"
#include "KingHouse.h"
#include "Smithy.h"
#include "MagicShop.h"
// 부쉬
#include "Bush1.h"
#include "Bush2.h"
#include "Bush3.h"
#include "Bush4.h"
#include "Bush5.h"
#include "Bush6.h"
#include "Bush7.h"
#include "Bush8.h"
#include "Bush9.h"
#include "Bush10.h"
#include "Bush11.h"
// 산
#include "Mountain_Grass.h"
#include "Mountain_Ice.h"
// 돌
#include "Rock1.h"
#include "Rock2.h"
#include "Rock3.h"
#include "Rock4.h"
// 기둥
#include "Rock_Pillar1.h"
#include "Rock_Pillar2.h"
#include "Rock_Pillar3.h"
#include "Ice_Pillar1.h"
#include "Temple_Pillar1.h"
#include "Temple_Pillar2.h"
// 던전
#include "Dungeon_Grass.h"
#include "Dungeon_Ice.h"
#include "Dungeon_Temple.h"
// 타워
#include "Tower1.h"
#include "Tower2.h"
#include "Tower3.h"
// 상자
#include "Chest_Cosmetic.h"
#include "Chest_Gold.h"
#include "Chest_Regular.h"

#include "Player.h"
#include "Player_Camera.h"
#include "Tool_Camera.h"
#include "EventMgr.h"
// UI
#include "LevelUI.h"
#include "TabUI.h"
#include "RingUI.h"
#include "ZoomUI.h"
#include "HpUI.h"
#include "ManaUI.h"
#include "DefUI.h"
#include "IndicatorUI.h"
#include "FieldSkillUI.h"
#include "DialogUI.h"

// NPC
#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"
#include "Npc_Soldier.h"
#include "Npc_Citizen1.h"
#include "Npc_Citizen2.h"

// Monster
#include "ExpUI.h"
#include "EnterUI.h"
#include "CuteMonster.h"
#include "Hedgehog.h"
#include "LineObject.h"
#include "Bat.h"
#include "Dragon.h"
#include "Ram.h"
#include "Fox.h"
#include "Wyvern.h"
#include "Squirrel.h"

// Effect
#include "Cloud1.h"
#include "Cloud2.h"
#include "Cloud3.h"

#include "Effect_Cast_Blue.h"
#include "Effect_Cast_Yellow.h"
#include "Effect_Cast_Purple.h"

#include "Effect_SpellBurst_Blue.h"
#include "Effect_SpellBurst_Purple.h"
#include "Effect_SpellBurst_Yellow.h"

#include "Effect_Fire.h"
#include "Effect_Lightning.h"
#include "Effect_Range_BigCircle.h"

// Item
#include "GoldCoin.h"
#include "ExpCoin.h"
#include "Key.h"

// Generator
#include "PollenGenerator.h"

CScene_World::CScene_World(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::WORLD)
{
}

CScene_World::~CScene_World()
{
}

HRESULT CScene_World::Ready_Scene()
{
	// 임의 순서 변경 X

	FAILED_CHECK_RETURN(Ready_Layer_Environment()	, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Camera()		, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Player()		, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Npc()			, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster()		, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Projectile()	, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Item()			, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Effect(), E_FAIL);
	
	return S_OK;
}

Engine::_int CScene_World::Update_Scene(const _float& fTimeDelta)
{
	__super::Update_Scene(fTimeDelta);

	return 0;
}

void CScene_World::LateUpdate_Scene()
{
	//CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::MONSTER);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ENVIRONMENT);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::NPC);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM);

	CCollisionMgr::GetInstance()->Check_Line_Collision(OBJ_TYPE::PLAYER);

	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM);

	__super::LateUpdate_Scene();

	CCameraMgr::GetInstance()->Set_ViewSpace();
}

void CScene_World::Render_Scene()
{
#pragma region Stack

	RECT	rc{};
	_vec3	vPos{};
	CGameObject*	pObj = nullptr;
	TCHAR	szBuf[MAX_STR] = L"";
	GetClientRect(g_hWnd, &rc);

#pragma endregion

	swprintf_s(szBuf, L"%.d FPS", _int(1.f / Engine::Get_TimeDelta(L"Timer_FPS65")));
	SCREEN_MSG(szBuf, rc);

	pObj = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
	NULL_CHECK(pObj);
	vPos = pObj->Get_Transform()->Get_Info(INFO_POS);
	swprintf_s(szBuf, L"PLAYER : %.3f,  %.3f,  %.3f", vPos.x, vPos.y, vPos.z);
	SCREEN_MSG(szBuf, rc);
}

void CScene_World::Free()
{
	__super::Free();
}

CScene_World* CScene_World::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_World*	pInstance = new CScene_World(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Scene_World Create Failed");
		return nullptr;
	}

	return pInstance;
}
HRESULT CScene_World::Ready_Layer_Environment()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

	// Terrain
	pGameObject = CTerrainWorld::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainWorld", pGameObject), E_FAIL);

#pragma region Building

	// House
	pGameObject = CHouse1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House1", pGameObject), E_FAIL);

	pGameObject = CHouse2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House2", pGameObject), E_FAIL);

	pGameObject = CHouse3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House3", pGameObject), E_FAIL);

	pGameObject = CHouse4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House4", pGameObject), E_FAIL);

	pGameObject = CHouse5::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House5", pGameObject), E_FAIL);

	pGameObject = CHouse6::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House6", pGameObject), E_FAIL);

	// King House
	pGameObject = CKingHouse::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"KingHouse", pGameObject), E_FAIL);

	// Smithy
	pGameObject = CSmithy::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Smithy", pGameObject), E_FAIL);

	// Magic Shop
	pGameObject = CMagicShop::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MagicShop", pGameObject), E_FAIL);

#pragma endregion
	
#pragma region Bush

	// Bush
	pGameObject = CBush1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush1", pGameObject), E_FAIL);

	pGameObject = CBush2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush2", pGameObject), E_FAIL);

	pGameObject = CBush3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush3", pGameObject), E_FAIL);

	pGameObject = CBush4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush4", pGameObject), E_FAIL);

	pGameObject = CBush5::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush5", pGameObject), E_FAIL);

	pGameObject = CBush6::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush6", pGameObject), E_FAIL);

	pGameObject = CBush7::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush7", pGameObject), E_FAIL);

	pGameObject = CBush8::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush8", pGameObject), E_FAIL);

	pGameObject = CBush9::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush9", pGameObject), E_FAIL);

	pGameObject = CBush10::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush10", pGameObject), E_FAIL);

	pGameObject = CBush11::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush11", pGameObject), E_FAIL);

#pragma endregion

#pragma region Mountain
	// Mountain
	pGameObject = CMountain_Grass::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain_Grass", pGameObject), E_FAIL);

	pGameObject = CMountain_Ice::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain_Ice", pGameObject), E_FAIL);
	
#pragma endregion

#pragma region Rock
	pGameObject = CRock1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock1", pGameObject), E_FAIL);

	pGameObject = CRock2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock2", pGameObject), E_FAIL);

	pGameObject = CRock3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock3", pGameObject), E_FAIL);

	pGameObject = CRock4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock4", pGameObject), E_FAIL);
#pragma endregion

#pragma region Pillar
	// Rock Pillar
	pGameObject = CRock_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar1", pGameObject), E_FAIL);

	pGameObject = CRock_Pillar2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar2", pGameObject), E_FAIL);

	pGameObject = CRock_Pillar3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar3", pGameObject), E_FAIL);
	// Temple Pillar
	pGameObject = CTemple_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Temple_Pillar1", pGameObject), E_FAIL);

	pGameObject = CTemple_Pillar2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Temple_Pillar2", pGameObject), E_FAIL);
	// Ice Pillar
	pGameObject = CIce_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Ice_Pillar1", pGameObject), E_FAIL);
#pragma endregion

#pragma region Dungeon
	// Dungeon
	pGameObject = CDungeon_Grass::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Grass", pGameObject), E_FAIL);

	// Line Test
	/*pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f - 20.f, 0.f, -20.f }, _vec3{ VTXCNTX * 0.5f, 0.f, 0.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_01", pGameObject), E_FAIL);

	pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f - 60.f, 0.f, -20.f }, _vec3{ VTXCNTX * 0.5f - 30.f, 0.f, 0.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_02", pGameObject), E_FAIL);*/


	/*pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f + 20.f, 0.f, 0.f }, _vec3{ VTXCNTX * 0.5f + 20.f, 0.f, 20.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_03", pGameObject), E_FAIL);*/

	//pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{  VTXCNTX * 0.5f + 40.f, 0.f, 20.f }, _vec3{ VTXCNTX * 0.5f + 40.f, 0.f, 0.f });
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_04", pGameObject), E_FAIL);


	/*pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f + 30.f, 0.f, -30.f }, _vec3{ VTXCNTX * 0.5f + 10.f, 0.f, -10.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_05", pGameObject), E_FAIL);*/


	//pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f + 50.f, 0.f, -30.f }, _vec3{ VTXCNTX * 0.5f + 30.f, 0.f, -30.f });
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_06", pGameObject), E_FAIL);

	pGameObject = CDungeon_Ice::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Ice", pGameObject), E_FAIL);

	pGameObject = CDungeon_Temple::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Temple", pGameObject), E_FAIL);
#pragma endregion

#pragma region Tower
	// Tower
	pGameObject = CTower1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower1", pGameObject), E_FAIL);

	pGameObject = CTower2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower2", pGameObject), E_FAIL);

	pGameObject = CTower3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower3", pGameObject), E_FAIL);
#pragma endregion

#pragma region Chest

	// Chest
	// Cosmetic Chest
	pGameObject = CChest_Cosmetic::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cosmetic_Chest", pGameObject), E_FAIL);

	// Gold Chest
	pGameObject = CChest_Gold::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Gold_Chest", pGameObject), E_FAIL);

	// Regular Chest
	pGameObject = CChest_Regular::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Regular_Chest", pGameObject), E_FAIL);

#pragma endregion
	
	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Camera()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::CAMERA, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

	// Camera
	pGameObject = CPlayer_Camera::Create(m_pGraphicDev);

	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Camera", pGameObject), E_FAIL);
	CCameraMgr::GetInstance()->Add_Camera(L"MainCamera", static_cast<CCameraObject*>(pGameObject));
	CCameraMgr::GetInstance()->Set_MainCamera(L"MainCamera");
	
	return S_OK;
}

HRESULT CScene_World::Ready_Layer_UI()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::UI, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;



	// UI - Level
	pGameObject = CLevelUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Level", pGameObject), E_FAIL);

	// UI - Tab
	pGameObject = CTabUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Tab", pGameObject), E_FAIL);

	// UI - Zoom
	pGameObject = CZoomUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Zoom", pGameObject), E_FAIL);


	// UI - Exp
	pGameObject = CExpUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Exp", pGameObject), E_FAIL);

	// UI - Hp
	pGameObject = CHpUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Hp", pGameObject), E_FAIL);

	// UI - Def
	pGameObject = CDefUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Def", pGameObject), E_FAIL);

	// UI - Mana
	pGameObject = CManaUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Mana", pGameObject), E_FAIL);

	// UI - Enter
	pGameObject = CEnterUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Enter", pGameObject), E_FAIL);

	// UI - Ring
	pGameObject = CRingUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Ring", pGameObject), E_FAIL);

	

	// UI - Indicator
	pGameObject = CIndicatorUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Indicator", pGameObject), E_FAIL);

	// UI - Indicator
	pGameObject = CFieldSkillUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_FieldSkill", pGameObject), E_FAIL);

	pGameObject = CDialogUI::Create(m_pGraphicDev, OBJ_ID::NPC_BLACKSMITH, L"그대 기억이 지난 사랑이 내안을 파고드는 가시가 되어 제발 가라고 아주 가라고 외쳐도 눈물만 흘리는데");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Dialog", pGameObject), E_FAIL);


	m_mapLayer.insert({ OBJ_TYPE::UI, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Player()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::PLAYER, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

	// Player
	pGameObject = CPlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player", pGameObject), E_FAIL);


	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Npc()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::NPC, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// King
	pGameObject = CNpc_King::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_King", pGameObject), E_FAIL);

	// Mage
	pGameObject = CNpc_Mage::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Mage", pGameObject), E_FAIL);
	
	// BlackSmith
	pGameObject = CNpc_BlackSmith::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_BlackSmith", pGameObject), E_FAIL);

	// Soldier
	pGameObject = CNpc_Soldier::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Soldier", pGameObject), E_FAIL);

	// Citizen1
	pGameObject = CNpc_Citizen1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Citizen1", pGameObject), E_FAIL);

	// Citizen2
	pGameObject = CNpc_Citizen2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Citizen2", pGameObject), E_FAIL);


	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Monster()
{
	//return S_OK;

	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::MONSTER, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

	// ============= Basic Mosnter
	//Hedgehog
	pGameObject = CHedgehog::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);

	// Ram
	pGameObject = CRam::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Ram", pGameObject), E_FAIL);

	// Fox
	pGameObject = CFox::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Fox", pGameObject), E_FAIL);

	// Squirrel
	pGameObject = CSquirrel::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Squirrel", pGameObject), E_FAIL);


	// =========== Fly Monster 
	//Bat
	pGameObject = CBat::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Bat", pGameObject), E_FAIL);


	// Wyvern
	pGameObject = CWyvern::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Wyvern", pGameObject), E_FAIL);


	// ========== Boss Monster
	// Dragon
	pGameObject = CDragon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Dragon", pGameObject), E_FAIL);


	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Item()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;
	m_mapLayer.insert({ OBJ_TYPE::ITEM, pLayer });


	// Gold
	pGameObject = CGoldCoin::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", pGameObject), E_FAIL);


	// Exp
	pGameObject = CExpCoin::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_ExpCoin", pGameObject), E_FAIL);

	// Key
	pGameObject = CKey::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_Key", pGameObject), E_FAIL);



	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Projectile()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;
	m_mapLayer.insert({ OBJ_TYPE::PROJECTILE, pLayer });


	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Effect()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject* pGameObject = nullptr;
	m_mapLayer.insert({ OBJ_TYPE::EFFECT, pLayer });

#pragma region KANG

	// Cloud
	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_1", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({80.f, 12.f, 102.f});

	pGameObject = CCloud2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud2_1", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 50.f, 12.f, 42.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_1", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 75.f, 12.f, 122.f });



	// 시연 끝나고 지울거
	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_2", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 90.f, 12.f, 72.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_3", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 100.f, 12.f, 112.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_4", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 50.f, 10.f, 70.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_5", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 40.f, 11.f, 110.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_2", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 10.f, 12.f, 40.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_3", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 120.f, 12.f, 40.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_4", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 125.f, 12.f, 150.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_5", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 145.f, 12.f, 130.f });

	pGameObject = CCloud2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud2_2", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 145.f, 12.f, 70.f });

	// Generator
	// pGameObject = CPollenGenerator::Create(m_pGraphicDev);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Pollen_Generator", pGameObject), E_FAIL);

#pragma endregion

#pragma region Chan

	pGameObject = CEffect_Cast_Blue::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Cast_Blue", pGameObject), E_FAIL);

	pGameObject = CEffect_Cast_Purple::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Cast_Purple", pGameObject), E_FAIL);

	pGameObject = CEffect_Cast_Yellow::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Cast_Yellow", pGameObject), E_FAIL);

	pGameObject = CEffect_SpellBrust_Blue::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Spellburst_Blue", pGameObject), E_FAIL);

	pGameObject = CEffect_SpellBrust_Purple::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Spellburst_Purple", pGameObject), E_FAIL);

	pGameObject = CEffect_SpellBrust_Yellow::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Spellburst_Yellow", pGameObject), E_FAIL);

	pGameObject = CEffect_Fire::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Fire", pGameObject), E_FAIL);

	pGameObject = CEffect_Lightning::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Lightning", pGameObject), E_FAIL);

	pGameObject = CEffect_Range_BigCircle::Create(m_pGraphicDev, nullptr);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Range_BigCircle_Orange", pGameObject), E_FAIL);

#pragma endregion

	return S_OK;
}
