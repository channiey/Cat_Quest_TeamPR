#include "stdafx.h"
#include "..\Header\Scene_Dungeon_Temple.h"

#include "Export_Function.h"

CScene_Dungeon_Temple::CScene_Dungeon_Temple(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::DUNGEON_TEMPLE)
{
}

CScene_Dungeon_Temple::~CScene_Dungeon_Temple()
{
}

HRESULT CScene_Dungeon_Temple::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	return S_OK;
}

Engine::_int CScene_Dungeon_Temple::Update_Scene(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Scene(fTimeDelta);

	return iExit;
}

void CScene_Dungeon_Temple::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CScene_Dungeon_Temple::Render_Scene()
{

}

void CScene_Dungeon_Temple::Free()
{
	__super::Free();
}

CScene_Dungeon_Temple* CScene_Dungeon_Temple::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Dungeon_Temple* pInstance = new CScene_Dungeon_Temple(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Scene Dungeon Temple Create Failed");
		return nullptr;
	}

	return pInstance;
}

HRESULT CScene_Dungeon_Temple::Ready_Prototype()
{

	return S_OK;
}

