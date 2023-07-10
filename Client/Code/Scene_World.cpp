#include "stdafx.h"
#include "..\Header\Scene_World.h"

#include "Export_Function.h"

#include "Terrain.h"
#include "TerrainWorld.h"
#include "Building.h"
#include "Forest.h"
#include "Mountain.h"
#include "Dungeon.h"

#include "Player.h"
#include "Player_Camera.h"
#include "Tool_Camera.h"
#include "EventMgr.h"
#include "LevelUI.h"
#include "TabUI.h"
#include "ManaBarUI.h"
#include "CuteMonster.h"
#include "Hedgehog.h"
#include "LineObject.h"
#include "Bat.h"

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
	CCollisionMgr::GetInstance()->Check_Line_Collision(OBJ_TYPE::PLAYER);

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

	// Building
	pGameObject = CBuilding::Create(m_pGraphicDev); 
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Building", pGameObject), E_FAIL);

	// Forest
	pGameObject = CForest::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Forest", pGameObject), E_FAIL);

	// Mountain
	pGameObject = CMountain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain", pGameObject), E_FAIL);

	// Dungeon
	pGameObject = CDungeon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon", pGameObject), E_FAIL);

	// Line Test
	pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f - 20.f, 0.f, -20.f }, _vec3{ VTXCNTX * 0.5f, 0.f, 0.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_01", pGameObject), E_FAIL);

	pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f - 60.f, 0.f, -20.f }, _vec3{ VTXCNTX * 0.5f - 30.f, 0.f, 0.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_02", pGameObject), E_FAIL);


	/*pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f + 20.f, 0.f, 0.f }, _vec3{ VTXCNTX * 0.5f + 20.f, 0.f, 20.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_03", pGameObject), E_FAIL);*/

	//pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{  VTXCNTX * 0.5f + 40.f, 0.f, 20.f }, _vec3{ VTXCNTX * 0.5f + 40.f, 0.f, 0.f });
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_04", pGameObject), E_FAIL);


	pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f + 30.f, 0.f, -30.f }, _vec3{ VTXCNTX * 0.5f + 10.f, 0.f, -10.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_05", pGameObject), E_FAIL);


	//pGameObject = CLineObject::Create(m_pGraphicDev, _vec3{ VTXCNTX * 0.5f + 50.f, 0.f, -30.f }, _vec3{ VTXCNTX * 0.5f + 30.f, 0.f, -30.f });
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LineObjct_06", pGameObject), E_FAIL);



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

	pGameObject = CHedgehog::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);

	pGameObject = CBat::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Bat", pGameObject), E_FAIL);


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