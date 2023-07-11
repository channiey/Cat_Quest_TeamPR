#include "stdafx.h"
#include "..\Header\Scene_Tool.h"

#include "Export_Function.h"

// #include "Terrain.h"
#include "TerrainWorld.h"
#include "TerrainTool.h"
#include "TerrainIceWorld.h"
#include "TerrainIceDungeon.h"
// ����(��)
#include "House1.h"
#include "House2.h"
#include "House3.h"
#include "House4.h"
#include "House5.h"
#include "House6.h"
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


// Monster
#include "ExpUI.h"
#include "EnterUI.h"
#include "Hedgehog.h"
#include "LineObject.h"
#include "Bat.h"
#include "Dragon.h"
#include "Ram.h"
#include "Fox.h"
#include "Wyvern.h"
#include "Squirrel.h"

#include "Player.h"
#include "CuteMonster.h"
#include "Environment.h"
#include "Tool_Camera.h"
#include "CameraTargetObj.h"

#include "ImGuiMgr.h"
#include "Calculator.h"

CScene_Tool::CScene_Tool(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::TOOL)
{
}

CScene_Tool::~CScene_Tool()
{
}

HRESULT CScene_Tool::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Layer_Camera(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Terrain(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Npc(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Item(), E_FAIL);

	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->ImGui_SetUp(m_pGraphicDev), E_FAIL);
	// ��� ������Ʈ�� ������ �� IMGUI�� ��� ������Ʈ���� ������ �޾ƿ;� �Ѵ�.

	return S_OK;
}

Engine::_int CScene_Tool::Update_Scene(const _float& fTimeDelta)
{
	__super::Update_Scene(fTimeDelta);

	CImGuiMgr::GetInstance()->ImGui_Update();

	return 0;
}

void CScene_Tool::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();

	CCameraMgr::GetInstance()->Set_ViewSpace();
}

void CScene_Tool::Render_Scene()
{
	CImGuiMgr::GetInstance()->ImGui_Render(); 
}

void CScene_Tool::Free()
{
	CImGuiMgr::GetInstance()->DestroyInstance();
	CCalculator::GetInstance()->DestroyInstance();
	__super::Free();
}

CScene_Tool* CScene_Tool::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Tool* pInstance = new CScene_Tool(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		
		MSG_BOX("Scene_Tool Create Failed");
		return nullptr;
	}

	return pInstance;
}
HRESULT CScene_Tool::Ready_Layer_Terrain()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::TERRAIN, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	 pGameObject = CTerrainWorld::Create(m_pGraphicDev);
	 NULL_CHECK_RETURN(pGameObject, E_FAIL);
	 FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainWorld", pGameObject), E_FAIL);

	// 
	// pGameObject = CTerrainIceWorld::Create(m_pGraphicDev);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainWorld_Ice", pGameObject), E_FAIL);

	// pGameObject = CTerrainIceDungeon::Create(m_pGraphicDev);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainDungeon_Ice", pGameObject), E_FAIL);

	// pGameObject = CTerrainTool::Create(m_pGraphicDev);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainTool", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Environment()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// Building
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


	// Mountain
	pGameObject = CMountain_Grass::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain_Grass", pGameObject), E_FAIL);

	pGameObject = CMountain_Ice::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain_Ice", pGameObject), E_FAIL);


	// Rock
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


	// Pillar
	pGameObject = CRock_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar1", pGameObject), E_FAIL);

	pGameObject = CRock_Pillar2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar2", pGameObject), E_FAIL);

	pGameObject = CRock_Pillar3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar3", pGameObject), E_FAIL);

	pGameObject = CTemple_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Temple_Pillar1", pGameObject), E_FAIL);

	pGameObject = CTemple_Pillar2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Temple_Pillar2", pGameObject), E_FAIL);

	pGameObject = CIce_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Ice_Pillar1", pGameObject), E_FAIL);


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


	// Chest
	pGameObject = CChest_Cosmetic::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cosmetic_Chest", pGameObject), E_FAIL);

	pGameObject = CChest_Gold::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Gold_Chest", pGameObject), E_FAIL);

	pGameObject = CChest_Regular::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Regular_Chest", pGameObject), E_FAIL);


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

	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT, pLayer });

	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Camera()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::CAMERA, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// Camera
	pGameObject = CTool_Camera::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Camera", pGameObject), E_FAIL);
	CCameraMgr::GetInstance()->Add_Camera(L"MainCamera", static_cast<CCameraObject*>(pGameObject));
	CCameraMgr::GetInstance()->Set_MainCamera(L"MainCamera");

	// Camera Target Obj -> Player
	pGameObject = CCameraTargetObj::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CameraTargetObj", pGameObject), E_FAIL);


	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Monster()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::MONSTER, pLayer });
	Engine::CGameObject* pGameObject = nullptr;

	//Bat
	pGameObject = CBat::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Bat", pGameObject), E_FAIL);

	// Dragon
	pGameObject = CDragon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Dragon", pGameObject), E_FAIL);

	// Hedgehog
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

	// Wyvern
	pGameObject = CWyvern::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Wyvern", pGameObject), E_FAIL);

	// Squirrel
	pGameObject = CSquirrel::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Squirrel", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Npc()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::NPC, pLayer });
	Engine::CGameObject* pGameObject = nullptr;



	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Item()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ITEM, pLayer });
	Engine::CGameObject* pGameObject = nullptr;



	return S_OK;
}
