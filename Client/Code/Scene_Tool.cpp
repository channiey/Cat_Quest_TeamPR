#include "stdafx.h"
#include "..\Header\Scene_Tool.h"

#include "Export_Function.h"

// #include "Terrain.h"
#include "TerrainWorld.h"
#include "TerrainTool.h"

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
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->ImGui_SetUp(m_pGraphicDev), E_FAIL)
	FAILED_CHECK_RETURN(Ready_Layer_Environment(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Camera(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster(), E_FAIL);

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
HRESULT CScene_Tool::Ready_Layer_Environment()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject* pGameObject = nullptr;

	// Terrain
	pGameObject = CTerrainWorld::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainWorld", pGameObject), E_FAIL);

	pGameObject = CTerrainTool::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainTool", pGameObject), E_FAIL);

	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT, pLayer });

	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Camera()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject* pGameObject = nullptr;

	// Camera
	pGameObject = CTool_Camera::Create(m_pGraphicDev);

	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Camera", pGameObject), E_FAIL);
	CCameraMgr::GetInstance()->Add_Camera(L"MainCamera", static_cast<CCameraObject*>(pGameObject));
	CCameraMgr::GetInstance()->Set_MainCamera(L"MainCamera");

	pGameObject = CCameraTargetObj::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CameraTargetObj", pGameObject), E_FAIL);

	m_mapLayer.insert({ OBJ_TYPE::CAMERA, pLayer });

	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Monster()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::MONSTER, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// pGameObject = CCuteMonster::Create(m_pGraphicDev);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// CEventMgr::GetInstance()->Add_Obj(L"Monster_01", pGameObject);

	return S_OK;
}
