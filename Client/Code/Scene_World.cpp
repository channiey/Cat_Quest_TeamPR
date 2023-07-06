#include "stdafx.h"
#include "..\Header\Scene_World.h"

#include "Export_Function.h"

#include "Terrain.h"
#include "Player.h"
#include "CuteMonster.h"
#include "Player_Camera.h"
#include "Tool_Camera.h"

CScene_World::CScene_World(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::WORLD)
{
}

CScene_World::~CScene_World()
{
}

HRESULT CScene_World::Ready_Scene()
{
	// ���� ���� ���� X

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

	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::MONSTER, COL_TYPE::RECT, COL_TYPE::RECT);

	return 0;
}

void CScene_World::LateUpdate_Scene()
{
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

	// Camera Pos
	vPos = CCameraMgr::GetInstance()->Get_CurCamera()->Get_Transform()->Get_Info(INFO_POS);
	swprintf_s(szBuf, L"CAM : %.2f, %.2f, %.2f", vPos.x, vPos.y, vPos.z);
	SCREEN_MSG(szBuf, rc);

	// Player Pos
	vPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS);
	swprintf_s(szBuf, L"PLAYER : %.2f, %.2f, %.2f", vPos.x, vPos.y, vPos.z);
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

	Engine::CGameObject*		pGameObject = nullptr;

	// Terrain
	pGameObject = CTerrain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain", pGameObject), E_FAIL);

	m_mapLayer.insert({ OBJ_TYPE::ENVIORMENT, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Camera()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	// Camera
	if (PLAY_MODE::TOOL != CManagement::GetInstance()->Get_PlayMode())
		pGameObject = CPlayer_Camera::Create(m_pGraphicDev);
	else
		pGameObject = CTool_Camera::Create(m_pGraphicDev);

	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Camera", pGameObject), E_FAIL);
	CCameraMgr::GetInstance()->Add_Camera(L"MainCamera", static_cast<CCameraObject*>(pGameObject));
	CCameraMgr::GetInstance()->Set_MainCamera(L"MainCamera");
	
	m_mapLayer.insert({ OBJ_TYPE::CAMERA, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_UI()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ OBJ_TYPE::UI, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Player()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	// Player
	pGameObject = CPlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Player", pGameObject), E_FAIL);

	m_mapLayer.insert({ OBJ_TYPE::PLAYER, pLayer });

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Monster()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	// Monster
	pGameObject = CCuteMonster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Monster_01", pGameObject), E_FAIL);

	m_mapLayer.insert({ OBJ_TYPE::MONSTER, pLayer });

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