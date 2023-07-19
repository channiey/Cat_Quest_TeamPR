#include "stdafx.h"
#include "..\Header\Scene_World.h"

#include "Export_Function.h"

// Environment
#include "Terrain.h"
#include "TerrainWorld.h"
#include "Bush.h"
#include "Mountain.h"
#include "Dungeon.h"
// ����
#include "House1.h"
#include "House2.h"
#include "House3.h"
#include "House4.h"
#include "House5.h"
#include "House6.h"
#include "KingHouse.h"
#include "Smithy.h"
#include "MagicShop.h"
// �ν�
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
// ��
#include "Mountain_Grass.h"
#include "Mountain_Ice.h"
// ��
#include "Rock1.h"
#include "Rock2.h"
#include "Rock3.h"
#include "Rock4.h"
// ���
#include "Rock_Pillar1.h"
#include "Rock_Pillar2.h"
#include "Rock_Pillar3.h"
#include "Ice_Pillar1.h"
#include "Temple_Pillar1.h"
#include "Temple_Pillar2.h"
// ����
#include "Dungeon_Grass.h"
#include "Dungeon_Ice.h"
#include "Dungeon_Temple.h"
// Ÿ��
#include "Tower1.h"
#include "Tower2.h"
#include "Tower3.h"
// ����
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
#include "Inventory.h"

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
#include "WyvernRed.h"
#include "Test_Mob.h"


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



#include "Effect_Range_Quater.h"

// Item
#include "GoldCoin.h"
#include "ExpCoin.h"
#include "Key.h"
#include "WarriorWeapon.h"
#include "MageWeapon.h"
#include "NinjaWeapon.h"

// Generator
#include "PollenGenerator.h"

#include "ImGuiMgr.h"
#include "TalkMgr.h"
#include "QuestMgr.h"


CScene_World::CScene_World(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::WORLD)
{
}

CScene_World::~CScene_World()
{
}

HRESULT CScene_World::Ready_Scene()
{
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/
	CTalkMgr::GetInstance()->Init(); // ��ũ �Ŵ��� �ʱ�ȭ
	CQuestMgr::GetInstance()->Init(); // ����Ʈ �Ŵ��� �ʱ�ȭ

	FAILED_CHECK_RETURN(Ready_Layer_Camera()		, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Terrain(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment()	, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Player()		, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Npc()			, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster()		, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Item()			, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Effect(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Etc(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Load(), E_FAIL);


	FAILED_CHECK_RETURN(Ready_Layer_KSH(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_KJM(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_LHJ(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_YC(), E_FAIL);

	return S_OK;
}

Engine::_int CScene_World::Update_Scene(const _float& fTimeDelta)
{
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/

	__super::Update_Scene(fTimeDelta);

	CQuestMgr::GetInstance()->Update(m_pGraphicDev); // ����Ʈ �Ŵ��� ������Ʈ

	return 0;
}

void CScene_World::LateUpdate_Scene()
{
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/

	// 00. �浹 ���� -> 1�� �浹 ó��
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ENVIRONMENT);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::NPC);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM);

	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::MONSTER, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::����ȭ ����
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::MONSTER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::PLAYER, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::����ȭ ����

	// 01. ����Ʈ ������Ʈ -> 2�� �浹 ó��
	__super::LateUpdate_Scene();

	// 02. ī�޶� ������ ����
	CCameraMgr::GetInstance()->Set_ViewSpace();
}
void CScene_World::Render_Scene()
{
	if (!CManagement::GetInstance()->Is_Debug()) return;
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

	NULL_CHECK(CCameraMgr::GetInstance()->Get_CurCamera());
	vPos = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewSpace().Eye;
	swprintf_s(szBuf, L"CAMERA : %.3f,  %.3f,  %.3f", vPos.x, vPos.y, vPos.z);
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

	//// Terrain
	//pGameObject = CTerrainWorld::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainWorld", pGameObject), E_FAIL);

	//// House
	//pGameObject = CHouse1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House1", pGameObject), E_FAIL);

	//pGameObject = CHouse2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House2", pGameObject), E_FAIL);

	//pGameObject = CHouse3::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House3", pGameObject), E_FAIL);

	//pGameObject = CHouse4::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House4", pGameObject), E_FAIL);

	//pGameObject = CHouse5::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House5", pGameObject), E_FAIL);

	//pGameObject = CHouse6::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House6", pGameObject), E_FAIL);

	//// King House
	//pGameObject = CKingHouse::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"KingHouse", pGameObject), E_FAIL);

	//// Smithy
	//pGameObject = CSmithy::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Smithy", pGameObject), E_FAIL);

	//// Magic Shop
	//pGameObject = CMagicShop::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MagicShop", pGameObject), E_FAIL);

	//
	//// Bush
	//pGameObject = CBush1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush1", pGameObject), E_FAIL);

	//pGameObject = CBush2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush2", pGameObject), E_FAIL);

	//pGameObject = CBush3::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush3", pGameObject), E_FAIL);

	//pGameObject = CBush4::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush4", pGameObject), E_FAIL);

	//pGameObject = CBush5::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush5", pGameObject), E_FAIL);

	//pGameObject = CBush6::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush6", pGameObject), E_FAIL);

	//pGameObject = CBush7::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush7", pGameObject), E_FAIL);

	//pGameObject = CBush8::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush8", pGameObject), E_FAIL);

	//pGameObject = CBush9::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush9", pGameObject), E_FAIL);

	//pGameObject = CBush10::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush10", pGameObject), E_FAIL);

	//pGameObject = CBush11::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush11", pGameObject), E_FAIL);

	//// Mountain
	//pGameObject = CMountain_Grass::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain_Grass", pGameObject), E_FAIL);

	//pGameObject = CMountain_Ice::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain_Ice", pGameObject), E_FAIL);
	//
	//// Rock
	//pGameObject = CRock1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock1", pGameObject), E_FAIL);

	//pGameObject = CRock2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock2", pGameObject), E_FAIL);

	//pGameObject = CRock3::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock3", pGameObject), E_FAIL);

	//pGameObject = CRock4::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock4", pGameObject), E_FAIL);

	//// Rock Pillar
	//pGameObject = CRock_Pillar1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar1", pGameObject), E_FAIL);

	//pGameObject = CRock_Pillar2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar2", pGameObject), E_FAIL);

	//pGameObject = CRock_Pillar3::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar3", pGameObject), E_FAIL);

	//// Temple Pillar
	//pGameObject = CTemple_Pillar1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Temple_Pillar1", pGameObject), E_FAIL);

	//pGameObject = CTemple_Pillar2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Temple_Pillar2", pGameObject), E_FAIL);

	//// Ice Pillar
	//pGameObject = CIce_Pillar1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Ice_Pillar1", pGameObject), E_FAIL);

	//// Dungeon
	//pGameObject = CDungeon_Grass::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Grass", pGameObject), E_FAIL);

	//// Enterance
	//pGameObject = CDungeon_Ice::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Ice", pGameObject), E_FAIL);

	//pGameObject = CDungeon_Temple::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Temple", pGameObject), E_FAIL);

	//// Tower
	//pGameObject = CTower1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower1", pGameObject), E_FAIL);

	//pGameObject = CTower2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower2", pGameObject), E_FAIL);

	//pGameObject = CTower3::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower3", pGameObject), E_FAIL);

	//// Cosmetic Chest
	//pGameObject = CChest_Cosmetic::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cosmetic_Chest", pGameObject), E_FAIL);

	//// Gold Chest
	//pGameObject = CChest_Gold::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Gold_Chest", pGameObject), E_FAIL);

	//// Regular Chest
	//pGameObject = CChest_Regular::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Regular_Chest", pGameObject), E_FAIL);
	
	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Load()
{
	TCHAR szLoadPath[MAX_STR] = L"../Bin/Data/Level/Dynamic_Obj.dat";
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->ImGui_SetDevice(m_pGraphicDev), E_FAIL);
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->Load_Scene(*szLoadPath), E_FAIL);
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

HRESULT CScene_World::Ready_Layer_Terrain()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::TERRAIN, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

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

	// UI - Dialog
	/*pGameObject = CDialogUI::Create(m_pGraphicDev, OBJ_ID::NPC_KING
		, L"�״� ����� ���� ����� ������ �İ��� ���ð� �Ǿ�");
	 NULL_CHECK_RETURN(pGameObject, E_FAIL);
	 FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Dialog", pGameObject), E_FAIL);*/

	// UI - Inventroy
	pGameObject = CInventory::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Inventory", pGameObject), E_FAIL);

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

	//// King
	//pGameObject = CNpc_King::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_King", pGameObject), E_FAIL);

	//// Mage
	//pGameObject = CNpc_Mage::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Mage", pGameObject), E_FAIL);
	//
	//// BlackSmith
	//pGameObject = CNpc_BlackSmith::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_BlackSmith", pGameObject), E_FAIL);

	//// Soldier
	//pGameObject = CNpc_Soldier::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Soldier", pGameObject), E_FAIL);

	//// Citizen1
	//pGameObject = CNpc_Citizen1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Citizen1", pGameObject), E_FAIL);

	//// Citizen2
	//pGameObject = CNpc_Citizen2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Citizen2", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Monster()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::MONSTER, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

	//// ============= Basic Mosnter
	////Hedgehog
	//pGameObject = CHedgehog::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);

	//// Ram
	//pGameObject = CRam::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Ram", pGameObject), E_FAIL);

	//// Fox
	//pGameObject = CFox::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Fox", pGameObject), E_FAIL);

	//// Squirrel
	//pGameObject = CSquirrel::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Squirrel", pGameObject), E_FAIL);


	//// =========== Fly Monster 
	////Bat
	//pGameObject = CBat::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Bat", pGameObject), E_FAIL);


	//// Wyvern
	//pGameObject = CWyvern::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Wyvern", pGameObject), E_FAIL);


	//// ========== Boss Monster
	//// Dragon
	//pGameObject = CDragon::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Dragon", pGameObject), E_FAIL);


	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Item()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;
	m_mapLayer.insert({ OBJ_TYPE::ITEM, pLayer });

	//// Object ==================
	//
	//// Gold
	//pGameObject = CGoldCoin::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", pGameObject), E_FAIL);


	//// Exp
	//pGameObject = CExpCoin::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_ExpCoin", pGameObject), E_FAIL);

	//// Key
	//pGameObject = CKey::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_Key", pGameObject), E_FAIL);

	//// Weapon ================

	//// Warrior
	//pGameObject = CWarriorWeapon::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_WarriorWeapon", pGameObject), E_FAIL);

	//// Mage
	//pGameObject = CMageWeapon::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_MageWeapon", pGameObject), E_FAIL);

	//// Ninja
	//pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_NinjaeWeapon", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Effect()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject* pGameObject = nullptr;
	m_mapLayer.insert({ OBJ_TYPE::EFFECT, pLayer });

	// Cloud
	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_1", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({180.f, 12.f, 202.f});

	pGameObject = CCloud2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud2_1", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 150.f, 12.f, 142.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_1", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 175.f, 12.f, 222.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_2", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 190.f, 12.f, 172.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_3", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 200.f, 12.f, 212.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_4", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 150.f, 10.f, 170.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_5", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 140.f, 11.f, 210.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_2", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 110.f, 12.f, 140.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_3", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 220.f, 12.f, 140.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_4", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 225.f, 12.f, 250.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_5", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 245.f, 12.f, 230.f });

	pGameObject = CCloud2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud2_2", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 245.f, 12.f, 170.f });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Etc()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::RANGE_OBJ, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_KSH()
{
	Engine::CGameObject* pGameObject = nullptr;

	//pGameObject = CHedgehog::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);
	// Warrior
	pGameObject = CWarriorWeapon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_WarriorWeapon", pGameObject), E_FAIL);

	// Mage
	pGameObject = CMageWeapon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_MageWeapon", pGameObject), E_FAIL);

	// Ninja
	pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_NinjaeWeapon", pGameObject), E_FAIL);

	// MageNpc
	pGameObject = CNpc_Mage::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Npc_Mage", pGameObject), E_FAIL);


	return S_OK;
}

HRESULT CScene_World::Ready_Layer_KJM()
{
	Engine::CGameObject* pGameObject = nullptr;

	//pGameObject = CHedgehog::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);

	 //Test WyvernRed
	pGameObject = CWyvernRed::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_WyvernRed", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_LHJ()
{
	Engine::CGameObject* pGameObject = nullptr;

	//pGameObject = CHedgehog::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_YC()
{
	return S_OK;

	Engine::CGameObject* pGameObject = nullptr;

	pGameObject = CEffect_Range_Quater::Create(m_pGraphicDev, nullptr, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Effect_Quater_Range_Test", pGameObject), E_FAIL);	

	_vec3 vPos{ START_POS_WORLD_X, 0.f, START_POS_WORLD_Z };
	pGameObject->Get_Transform()->Set_Pos(vPos);

	return S_OK;
}
