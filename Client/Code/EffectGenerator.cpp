#include "stdafx.h"
#include "EffectGenerator.h"
#include "Pollen.h"
#include "Export_Function.h"

CEffectGenerator::CEffectGenerator(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::GENERATOR, OBJ_ID::GENERATOR_POLLEN)
	
{
}

CEffectGenerator::CEffectGenerator(const CEffectGenerator& rhs)
	: Engine::CGameObject(rhs)
{
}

CEffectGenerator::~CEffectGenerator()
{
}

HRESULT CEffectGenerator::Ready_Object()
{
	m_fPollen_AccTime = 0.f;
	Pollen_Caculate_CreateTime();

	return S_OK;
}

_int CEffectGenerator::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	switch (m_ePlayerLocate)
	{
	case OBJ_ID::ISLAND_RANGE_VILLAGE:
		Pollen_Create(fTimeDelta);
		break;
	case OBJ_ID::ISLAND_RANGE_ICE:
		break;
	case OBJ_ID::ISLAND_RANGE_JUMP:
		break;
	case OBJ_ID::ISLAND_RANGE_KING:
		break;
	case OBJ_ID::ISLAND_RANGE_DEATH:
		break;
	case OBJ_ID::TYPEEND:
		Pollen_Create(fTimeDelta);
		break;
	default:
		Pollen_Create(fTimeDelta);
		break;
	}

	

	return iExit;
}

void CEffectGenerator::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffectGenerator::Render_Object()
{
}

void CEffectGenerator::Pollen_Create(const _float& fTimeDelta)
{
	m_fPollen_AccTime += fTimeDelta;
	if (m_fPollen_AccTime >= m_fPollen_CreateTime)
	{
		Pollen_Caculate_InitPos();

		CGameObject* pPollen = CPollen::Create(m_pGraphicDev, m_vPollen_CreatePos);
		NULL_CHECK(pPollen);
		CEventMgr::GetInstance()->Add_Obj(L"Effect_Pollen", pPollen);

		m_fPollen_AccTime -= m_fPollen_CreateTime;
		Pollen_Caculate_CreateTime();
	}
}

void CEffectGenerator::Pollen_Caculate_CreateTime()
{
	_float fMin = 1.f;
	_float fMax = 2.f;
	_float fGenerTime = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	m_fPollen_CreateTime = floor(fGenerTime * 10) / 10;
}

void CEffectGenerator::Pollen_Caculate_InitPos()
{
	CGameObject* pPlayer = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
	NULL_CHECK(pPlayer);

	_vec3 vInitPos = pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS);

	vInitPos.x -= 40.f;

	_float fMin = -2.f;
	_float fMax = 1.f;
	_float vInitZ = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	vInitPos.z += floor(vInitZ * 10) / 10;
	m_vPollen_CreatePos = vInitPos;
}

void CEffectGenerator::Cloud_Create(const _float& fTimeDelta)
{
}

void CEffectGenerator::Cloud_Caculate_CreateTime()
{
}

void CEffectGenerator::Cloud_Caculate_InitPos()
{
}

CEffectGenerator* CEffectGenerator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEffectGenerator* pInstance = new CEffectGenerator(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("EffectGenerator Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffectGenerator::Free()
{
	__super::Free();
}
