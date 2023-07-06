#include "stdafx.h"
#include "..\Header\TerrainWorld.h"

#include "Export_Function.h"

CTerrainWorld::CTerrainWorld(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTerrain(pGraphicDev)
{
}

CTerrainWorld::CTerrainWorld(const CTerrain& rhs)
	: CTerrain(rhs)
{
}

CTerrainWorld::~CTerrainWorld()
{
}

HRESULT CTerrainWorld::Ready_Object(void)
{
	CTerrain::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTerrainWorld::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CTerrain::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return _int();
}

void CTerrainWorld::LateUpdate_Object(void)
{
	CTerrain::LateUpdate_Object();
}

void CTerrainWorld::Render_Object(void)
{
	CTerrain::Render_Object();
}

HRESULT CTerrainWorld::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CTerrainTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_TEX, pComponent);

	return S_OK;
}

CTerrainWorld* CTerrainWorld::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrainWorld* pInstance = new CTerrainWorld(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Terrain Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTerrainWorld::Free()
{
	CTerrain::Free();
}
