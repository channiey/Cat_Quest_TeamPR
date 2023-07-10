#include "stdafx.h"
#include "..\Header\Scene_World.h"

#include "Export_Function.h"

#include "Terrain.h"
#include "TerrainWorld.h"
#include "Bush.h"
#include "Mountain.h"
#include "Dungeon.h"
// 빌딩(집)
#include "House1.h"
#include "House2.h"
#include "House3.h"
#include "House4.h"
#include "House5.h"
#include "House6.h"
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
#include "LevelUI.h"
#include "TabUI.h"
#include "ManaBarUI.h"

#include "CuteMonster.h"
#include "Hedgehog.h"

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
	FAILED_CHECK_RETURN(Ready_Layer_UI()			, E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Player()		, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster()		, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Projectile()	, E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Item()			, E_FAIL);

	return S_OK;
}

Engine::_int CScene_World::Update_Scene(const _float& fTimeDelta)
{
	__super::Update_Scene(fTimeDelta);

	return 0;
}

void CScene_World::LateUpdate_Scene()
{
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::MONSTER);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ENVIRONMENT);

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

	// FPS
	swprintf_s(szBuf, L"FPS : %.d", _int(1.f / Engine::Get_TimeDelta(L"Timer_FPS65")));
	SCREEN_MSG(szBuf, rc);

	//// Camera Pos
	//vPos = CCameraMgr::GetInstance()->Get_CurCamera()->Get_Transform()->Get_Info(INFO_POS);
	//swprintf_s(szBuf, L"CAM : %.2f, %.2f, %.2f", vPos.x, vPos.y, vPos.z);
	//SCREEN_MSG(szBuf, rc);

	//// Player Pos
	//vPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS);
	//swprintf_s(szBuf, L"PLAYER : %.2f, %.2f, %.2f", vPos.x, vPos.y, vPos.z);
	//SCREEN_MSG(szBuf, rc);
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
	// Buliding(집)
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

	// UI - ManaBar
	pGameObject = CManaBarUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_ManaBar", pGameObject), E_FAIL);


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

HRESULT CScene_World::Ready_Layer_Monster()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::MONSTER, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

	// Monster
	pGameObject = CCuteMonster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_01", pGameObject), E_FAIL);

	pGameObject = CCuteMonster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_02", pGameObject), E_FAIL);

	pGameObject = CCuteMonster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_03", pGameObject), E_FAIL);

	pGameObject = CCuteMonster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_04", pGameObject), E_FAIL);

	pGameObject = CCuteMonster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_05", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Item()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;
	m_mapLayer.insert({ OBJ_TYPE::ITEM, pLayer });


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