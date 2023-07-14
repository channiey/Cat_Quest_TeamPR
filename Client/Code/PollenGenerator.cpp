#include "stdafx.h"
#include "PollenGenerator.h"

#include "Export_Function.h"

#include "Pollen.h"

#include <iostream>

CPollenGenerator::CPollenGenerator(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::GENERATOR, OBJ_ID::GENERATOR_POLLEN)
	
{
}

CPollenGenerator::CPollenGenerator(const CPollenGenerator& rhs)
	: Engine::CGameObject(rhs)
{
}

CPollenGenerator::~CPollenGenerator()
{
}

HRESULT CPollenGenerator::Ready_Object()
{
	m_fCreatTime = GetTickCount64() + 500;

	return S_OK;
}

_int CPollenGenerator::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);


    D3DXMATRIX matWorld = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatWorld();

	return iExit;
}

void CPollenGenerator::LateUpdate_Object()
{
	if (m_fCreatTime < GetTickCount64()) {
		CEventMgr::GetInstance()->Add_Obj(L"Pollen", CPollen::Create(m_pGraphicDev, m_vecCreatePos));
		m_fCreatTime = GetTickCount64() + 500;
	}
	
	__super::LateUpdate_Object();
}

void CPollenGenerator::Render_Object()
{
}

CPollenGenerator* CPollenGenerator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPollenGenerator* pInstance = new CPollenGenerator(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CameraTargetObj Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPollenGenerator::Free()
{
	__super::Free();
}
