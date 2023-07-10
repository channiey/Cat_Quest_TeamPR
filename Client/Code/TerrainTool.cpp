#include "stdafx.h"
#include "..\Header\TerrainTool.h"

#include "Export_Function.h"

CTerrainTool::CTerrainTool(LPDIRECT3DDEVICE9 pGraphicDev)
	:	CTerrain(pGraphicDev)
{
	m_bTool = true;
}

CTerrainTool::CTerrainTool(const CTerrain& rhs)
	:	CTerrain(rhs)
{
}

CTerrainTool::~CTerrainTool()
{
}

HRESULT CTerrainTool::Ready_Object(void)
{
	CTerrain::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTerrainTool::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CTerrain::Update_Object(fTimeDelta);

	return _int();
}

void CTerrainTool::LateUpdate_Object(void)
{
	CTerrain::LateUpdate_Object();
}

void CTerrainTool::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	CTerrain::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CTerrainTool::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CTerrainTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_TEX, pComponent);

	return S_OK;
}

CTerrainTool* CTerrainTool::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrainTool* pInstance = new CTerrainTool(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TerrainTool Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTerrainTool::Free()
{
	CTerrain::Free();
}
