#include "Export_Utility.h"

IMPLEMENT_SINGLETON(CManagement)

/* 툴모드로 시작할지, 게임모드로 시작할지 m_ePlayMode(PLAY_MODE::GAME) 매개변수로 결정하면 됩니다. */
/* 디버그 모드로 시작하면, 현재 FPS, 플레이어 위치, 콜라이더 등이 렌더됩니다 'P'키로 런타임중 전환이 가능합니다. */
CManagement::CManagement() : m_pScene(nullptr)
			, m_ePlayMode(PLAY_MODE::TOOL)
			, m_eGameStatus(GAME_STATUS::PLAYING)
			, m_bDebug(FALSE)
{
}

CManagement::~CManagement()
{
	Free();
}

_int CManagement::Update_Scene(const _float& fTimeDelta)
{
	if (nullptr == m_pScene)
		return -1;

	return m_pScene->Update_Scene(fTimeDelta);
}

void CManagement::LateUpdate_Scene()
{
	if (nullptr == m_pScene)
		return;

	m_pScene->LateUpdate_Scene();
}

void CManagement::Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	if (m_pScene)
		m_pScene->Render_Scene();			
}

CGameObject * CManagement::Get_GameObject(const OBJ_TYPE & _eObjType, const _tchar * pObjTag)
{
	return m_pScene->Get_GameObject(_eObjType, pObjTag);
}

CComponent * CManagement::Get_Component(const OBJ_TYPE& _eObjType, const _tchar * pObjTag, const COMPONENT_TYPE& _eComponentType, COMPONENTID eID)
{
	if (nullptr == m_pScene)
		return nullptr;

	return m_pScene->Get_Component(_eObjType, pObjTag, _eComponentType, eID);
}

CLayer * CManagement::Get_Layer(const OBJ_TYPE& _eType)
{
	return 	m_pScene->Get_Layer(_eType);
}

HRESULT CManagement::Set_Scene(CScene * pScene)
{
	Safe_Release(m_pScene);
	
	m_pScene = pScene;

	return S_OK;
}

HRESULT CManagement::Add_Object(const OBJ_TYPE & _eObjType, const _tchar * _pObjTag, CGameObject* _pObj)
{
	if (m_pScene->Add_Object(_eObjType, _pObjTag, _pObj))
		return S_OK;

	return E_FAIL;
}

void CManagement::Free()
{
	Safe_Release(m_pScene);
}
