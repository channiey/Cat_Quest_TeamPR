#include "stdafx.h"
#include "PollenGenerator.h"
#include "Pollen.h"
#include "Export_Function.h"

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
	m_fAccTime = 0.f;
	Caculate_CreateTime();

	return S_OK;
}

_int CPollenGenerator::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	m_fAccTime += fTimeDelta;
	if (m_fAccTime > m_fCreateTime)
	{
		Caculate_InitPos();

		CGameObject* pPollen = CPollen::Create(m_pGraphicDev, m_vecCreatePos);
		NULL_CHECK_RETURN(pPollen , E_FAIL);
		CEventMgr::GetInstance()->Add_Obj(L"Effect_Pollen", pPollen);

		m_fAccTime = 0.f;
		Caculate_CreateTime();
	}

	return iExit;
}

void CPollenGenerator::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CPollenGenerator::Render_Object()
{
}

void CPollenGenerator::Caculate_CreateTime()
{
	_float fMin = 0.8f;
	_float fMax = 2.f;
	_float fGenerTime = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	m_fCreateTime = floor(fGenerTime * 10) / 10;
}

void CPollenGenerator::Caculate_InitPos()
{
	CGameObject* pPlayer = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
	NULL_CHECK(pPlayer);

	_vec3 vInitPos = pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS);

	vInitPos.x -= 40.f;

	_float fMin = -2.f;
	_float fMax = 1.f;
	_float vInitZ = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	vInitPos.z += floor(vInitZ * 10) / 10;
	m_vecCreatePos = vInitPos;
}

CPollenGenerator* CPollenGenerator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPollenGenerator* pInstance = new CPollenGenerator(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("PllenGenerator Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPollenGenerator::Free()
{
	__super::Free();
}
