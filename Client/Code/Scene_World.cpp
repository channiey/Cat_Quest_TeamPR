#include "stdafx.h"
#include "..\Header\Scene_World.h"

#include "Export_Function.h"

#include "Transform.h"

#include "TwinPeaks.h"
#include "DeathTree.h"
#include "TripleDeathTree.h"
#include "WorldTree.h"
#include "Grass1.h"
#include "Tombstone.h"
#include "PirateHideOut.h"
#include "Sweets1.h"
#include "Sweets2.h"

// Environment
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
#include "Inventory.h"
#include "FlightUI.h"
#include "DungeonTextUI.h"

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
#include "Serpent.h"
#include "Fish.h"
#include "VioletDragon.h"

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

#include "Effect_FlyLighting.h"

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

#include "Scene_Dungeon_Swamp.h"

#include "FadeUI.h"
//Projectile
#include "FoxFire.h"
#include "Chase_Bullet.h"

#include "TerrainTool.h"

CScene_World::CScene_World(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::WORLD)
{
}

CScene_World::~CScene_World()
{
}

HRESULT CScene_World::Ready_Scene()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/
	FAILED_CHECK_RETURN(Ready_Layer_Camera(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(),		E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Player(),	E_FAIL); // 퀘스트 매니저 Init 실행.
	FAILED_CHECK_RETURN(Ready_Layer_Effect(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Other(),	E_FAIL);

	FAILED_CHECK_RETURN(Ready_Load(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_KSH(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_KJM(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_LHJ(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_YC(),	E_FAIL);

	// 한 번만 초기화

	if (!CTalkMgr::GetInstance()->Get_IsInit()) CTalkMgr::GetInstance()->Init(); // 토크 매니저 초기화

	return S_OK;
}

Engine::_int CScene_World::Update_Scene(const _float& fTimeDelta)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	if (!m_bStartFade)
	{
		if (!CManagement::GetInstance()->Is_Enter_InGame())
		{
			CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::SCENE_ENTER_INGAME);
			CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::ENTER_WORLD);
			CManagement::GetInstance()->Set_Enter_InGame(TRUE);
		}
		else
		{
			CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::SCENE_ENTER_FIELD);
			CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::BLACK_FADE_IN);
		}
		m_bStartFade = TRUE;
	}

	__super::Update_Scene(fTimeDelta);

	CQuestMgr::GetInstance()->Update(m_pGraphicDev); // 퀘스트 매니저 업데이트

	return 0;
}

void CScene_World::LateUpdate_Scene()
{
	
	if (CInputDev::GetInstance()->Key_Down('N'))
	{
		_vec3 vPlayerPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS);
		_vec3 vTargetPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_King")->Get_Transform()->Get_Info(INFO_POS);
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, vPlayerPos, vTargetPos, TRUE);
	}
	if (CInputDev::GetInstance()->Key_Down('M'))
	{
		_vec3 vPlayerPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS);
		_vec3 vTargetPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_King")->Get_Transform()->Get_Info(INFO_POS);
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, vTargetPos, vPlayerPos);
	}
	
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	// 00. 1차 충돌 처리
	
	// Rect vs Rect
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ENVIRONMENT);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::NPC);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::MONSTER, OBJ_TYPE::PROJECTILE);

	// Rect vs Line
	CCollisionMgr::GetInstance()->Check_Line_Collision(OBJ_TYPE::PLAYER);

	// Position vs Sphere 
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::MONSTER, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::MONSTER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::PLAYER, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::MONSTER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::SKILL, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능


	// 01. 레이트 업데이트 -> 2차 충돌 처리
	__super::LateUpdate_Scene();

	// 02. 카메라 포지션 결정
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

	swprintf_s(szBuf, L"C : 속도 증가 \tV : 원래 속도 \tJ : 풀 체력 \t K : 풀 마나");
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


HRESULT CScene_World::Ready_Load()
{
	TCHAR szLoadPath[MAX_STR] = L"../Bin/Data/Level/Level_World.dat";
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->ImGui_SetDevice(m_pGraphicDev), E_FAIL);
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->Load_Scene(szLoadPath), E_FAIL);
}

HRESULT CScene_World::Ready_Layer_Camera()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::CAMERA, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

	// Camera
	if (nullptr == CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::CAMERA, L"Player_Camera"))
	{
		pGameObject = CPlayer_Camera::Create(m_pGraphicDev);

		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_Camera", pGameObject), E_FAIL);
		CCameraMgr::GetInstance()->Add_Camera(L"MainCamera", static_cast<CCameraObject*>(pGameObject));
		CCameraMgr::GetInstance()->Set_MainCamera(L"MainCamera");
	}
	
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

	// UI - FieldSkill
	pGameObject = CFieldSkillUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_FieldSkill", pGameObject), E_FAIL);

	// UI - Inventroy
	// pGameObject = CInventory::Create(m_pGraphicDev);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Inventory", pGameObject), E_FAIL);
	// pGameObject->Set_Maintain(true);

	// UI - Flight
	pGameObject = CFlightUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Flight", pGameObject), E_FAIL);

	m_mapLayer.insert({ OBJ_TYPE::UI, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Player()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::PLAYER, pLayer });

	Engine::CGameObject* pGameObject = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");

	if (nullptr == pGameObject)
	{
		// Player
		pGameObject = CPlayer::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player", pGameObject), E_FAIL);
	
		if (!CQuestMgr::GetInstance()->Get_IsInit()) 
			CQuestMgr::GetInstance()->Init(m_pGraphicDev, pGameObject); // 퀘스트 매니저 초기화
	}
	else
	{
		pGameObject->Get_Transform()->Set_Pos(_vec3{ _float(START_POS_WORLD_X)
			, pGameObject->Get_Transform()->Get_Scale().y
			, _float(START_POS_WORLD_Z) });
	}
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

HRESULT CScene_World::Ready_Layer_Other()
{
	Engine::CLayer* pLayer = nullptr;
	
	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::TERRAIN,		pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT,	pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::RANGE_OBJ,	pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::LINE,			pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::SKILL,		pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::NPC,			pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::MONSTER,		pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ITEM,			pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::PROJECTILE,	pLayer });

	return S_OK;
}



HRESULT CScene_World::Ready_Layer_KSH()
{
	Engine::CGameObject* pGameObject = nullptr;

	//// MageNpc
	//pGameObject = CNpc_Mage::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Npc_Mage", pGameObject), E_FAIL);

	//// TwinPeaks
	//pGameObject = CTwinPeaks::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TwinPeaks", pGameObject), E_FAIL);

	//// Death Tree
	//pGameObject = CDeathTree::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"DeathTree", pGameObject), E_FAIL);

	//// Triple Death Tree
	//pGameObject = CTripleDeathTree::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TripleDeathTree", pGameObject), E_FAIL);

	//// World Tree
	//pGameObject = CWorldTree::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"WorldTree", pGameObject), E_FAIL);

	//// Grass
	//pGameObject = CGrass1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Grass1", pGameObject), E_FAIL);

	//// Tombstone
	//pGameObject = CTombstone::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Tombstone", pGameObject), E_FAIL);

	//// PirateHideOut
	//pGameObject = CPirateHideOut::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"PirateHideOut", pGameObject), E_FAIL);

	//// Sweets
	//pGameObject = CSweets1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"CSweets1", pGameObject), E_FAIL);

	//pGameObject = CSweets2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"CSweets2", pGameObject), E_FAIL);


	return S_OK;
}

HRESULT CScene_World::Ready_Layer_KJM()
{
	Engine::CGameObject* pGameObject = nullptr;

	//pGameObject = CHedgehog::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);

	// //Test WyvernRed
	//pGameObject = CWyvernRed::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_WyvernRed", pGameObject), E_FAIL);

	//// Fox
	//pGameObject = CFox::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Fox", pGameObject), E_FAIL);


	//// Serpent
	//pGameObject = CSerpent::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Serpent", pGameObject), E_FAIL);


	//// Fish
	//pGameObject = CFish::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Fish", pGameObject), E_FAIL);

	//// Violet Dragon  - Test 
	//pGameObject = CVioletDragon::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_VioletDragon", pGameObject), E_FAIL);

	//// Violet Dragon
	//pGameObject = CVioletDragon::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_VioletDragon", pGameObject), E_FAIL);

	//// Projcetile - Fox Fire - TEST
	//pGameObject = CFoxFire::Create(m_pGraphicDev, { 180,2.f,180 }, {1,0,0});
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Projectile_FoxFire ", pGameObject), E_FAIL);





	return S_OK;
}

HRESULT CScene_World::Ready_Layer_LHJ()
{
	Engine::CGameObject* pGameObject = nullptr;

	pGameObject = CTerrainTool::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Terrain_Tool", pGameObject), E_FAIL);

	pGameObject = CDungeonTextUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Text_UI", pGameObject), E_FAIL);

	//pGameObject = CHedgehog::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_YC()
{
	/*Engine::CGameObject* pGameObject = nullptr;
	
	_vec3 vStartPos{ START_POS_WORLD_X, 0.2f, START_POS_WORLD_Z };
	_vec3 vEndPos = vStartPos + _vec3{ 10.f , 0.2f, -10.f };

	pGameObject = CLineObject::Create(m_pGraphicDev, vStartPos, vEndPos);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Line Obj_01", pGameObject), E_FAIL);

	pGameObject = CLineObject::Create(m_pGraphicDev, vEndPos, vEndPos + _vec3{ 10.f, 0.f, 0.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Line Obj_02", pGameObject), E_FAIL);

	pGameObject = CLineObject::Create(m_pGraphicDev, vEndPos + _vec3{ 10.f, 0.f, 0.f }, vEndPos + _vec3{ 10.f, 0.f, -10.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Line Obj_03", pGameObject), E_FAIL);*/

	return S_OK;
}
